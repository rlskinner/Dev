#include	<stdio.h>
#include	<stdlib.h>
#include	<math.h>
#include	<limits.h>
#include	<assert.h>
#include	<bstring.h>

#include	"cellArray.h"


randArray::randArray( size_t _dataSize )
{
	dataSize = _dataSize;
	maxSize = 8;
	size = 0;
	data = new u_char[dataSize*(maxSize+1)];
	wts = new double[maxSize+1];
	cumWts = new double[2*(maxSize+1)+1];
	for( int i=1; i<=2*maxSize; i++ ) 
		cumWts[i] = 0.0;

	indUsed = 0;
	indSize = 8;
	inds = new int[indSize];

	autoUpdate = 1;

	printSets = getenv( "TD_PRINT_ARRAY_SETS" ) != NULL;
}



//
//  set weight at hi and adjust tree on up
//
void
randArray::incUpdate( int hi )
{
	while( hi > 0 ) {
		int left = hi << 1;
		cumWts[hi] = wts[hi] + cumWts[left] + cumWts[left+1];
		hi >>= 1;
	}

}


//
//  adjust the entire tree, after numerous additions
//
void
randArray::update()
{
	int	heap = 2*size;
	int	up = heap >> 1;
	while( heap >= 2 ) {
		cumWts[up] = wts[up] + cumWts[heap] + cumWts[heap+1];
		heap -= 2;
		up--;
	}
}

void
randArray::assertHeap()
{
#if	0
	//  assert validity of heap
	for( int i=1; i<=size; i++ ) {
		assert( cumWts[i] == wts[i] + cumWts[2*i] + cumWts[2*i+1]);
	}
#endif
}

int
randArray::addData( void *newData, double weight )
{
	int	hi;			// heap index where new cell index goes

	//
	//  see if there are empty indices, 
	//	if so, use one of them
	//
		assertHeap();
	if( indUsed > 0 ) {
		hi = inds[--indUsed];
	} else {
		
		//
		//  must add at end, make sure heap is big enough
		//
		if( size == maxSize ) {
			maxSize *= 2;
			// int	*newData = new int[nDim*(maxSize+1)];
			// bcopy( data, newData, nDim*(size+1)*sizeof(int) );
			// delete data;
			// data = newData;
			data = (u_char*)realloc( data, dataSize*(maxSize+1) );
	
			// double	*newW = new double[maxSize+1];
			// bcopy( wts, newW, (size+1)*sizeof(double) );
			// delete wts;
			// wts = newW;
			wts = (double*)realloc( wts, (maxSize+1)*sizeof(double) );
	
			// maintain extra large heap
			// double	*newCw = new double[2*(maxSize+1)+1];
			// bcopy( cumWts, newCw, (size+1)*sizeof(double) );
			// for( int i=size+1; i<=2*maxSize; i++ ) {
				// newCw[i] = 0.0;
			// }
			// delete cumWts;
			// cumWts = newCw;
			cumWts = (double*)realloc( cumWts, 2*(maxSize+1)*sizeof(double) );
		}
		size++;

		// maintain extra large heap
		cumWts[2*size] = 0.0;
		cumWts[2*size+1] = 0.0;

		hi = size;
	}

	bcopy( newData, &data[hi*dataSize], dataSize ); 

	//
	//  add this weight to heap
	//
	setWt( hi, weight );		// XXX did I want to add?

	assertHeap();
	return hi;
}



//
//  SET weight, do not add
//	wt <= 0.0 is NOT allowed
//
void
randArray::setWt( int heap, double wt ) 
{
    assert( wt > 0.0 );
    wts[heap] = wt;
    if( printSets )
	printf( "randArray::setWt( %d, %g )\n", heap, wt );
    if( autoUpdate )
        incUpdate( heap );
}


//
//  clear weight so this item can be "removed"
//
void
randArray::clearWt( int heap )
{
    wts[heap] = 0.0;
    if( autoUpdate )
	incUpdate( heap );
}


void
randArray::pick( void *pickData )
{
	//
	//  find random number 0.0 <= r <= total weight
	//
	double	normRand = double(random()) / double(INT_MAX);
	double	pickRand = getTotalWt()*normRand;

	//
	//  traverse down the tree, finding where pickRand goes
	//
	int	li = 1;				// logical index
	while( 1 ) {				// until we break
		int left = 2*li;		// logical, again

		if( pickRand < cumWts[left] ) {
			li = left;		// go to left subtree
		} else {
			pickRand -= cumWts[left];// this many fewer to deal with
			int right = left+1;
			if( pickRand < cumWts[right] ) {
				li = right;	// go to right subtree
			} else {
				break;		// what's left over is here
			}
		}
	}


	//
	//  we picked li
	//	set index
	//	save index for reuse
	//	set this index to zero
	//
	bcopy( &data[li*dataSize], pickData, dataSize );
	if( indUsed == indSize ) {
		indSize *= 2;
		inds = (int*)realloc( inds, indSize*sizeof(int) );
	}
	inds[indUsed++] = li;
	clearWt( li );
}


cellArray::cellArray( int nd, int d[] )
{
	setCntr = 0;
	nDim = nd;
	dims = new int[nDim];
	indexOffsets = new int[nDim];

	totalCount = 1;
	for( int i=0; i<nd; i++ ) {
		dims[i] = d[i];
		indexOffsets[i] = totalCount;// must be *before* total increased
		totalCount *= dims[i];
	}

	states = new char[totalCount];
	cellData = new cellDataUnion[totalCount];
	for( i=0; i<totalCount; i++ ) {
		states[i] = csEmpty;
		// cellData[i] = 0;		// so add() can just accumulate
	}

	waitList = new randArray( nDim*sizeof(int) );

	printPicks = getenv( "TD_PRINT_PICKS" ) != NULL;
}


void
cellArray::init( eat* ) {}



int
cellArray::numWaiting()
{
	return waitList->numWaiting();
}



//
//  unrolled loop for most common cases
//
int
cellArray::offset( int index[] )
{
	if( nDim == 2 ) {
		if( index[0] < 0 || index[0] >= dims[0] ||
		    index[1] < 0 || index[1] >= dims[1] )
			return -1;
		return index[0]*indexOffsets[0] + 
		       index[1]*indexOffsets[1];
	}

	if( nDim == 3 ) {
		if( index[0] < 0 || index[0] >= dims[0] ||
		    index[1] < 0 || index[1] >= dims[1] ||
		    index[2] < 0 || index[2] >= dims[2] )
			return -1;
		return index[0]*indexOffsets[0] + 
		       index[1]*indexOffsets[1] + 
		       index[2]*indexOffsets[2];
	}

	//
	//  the most general case
	//
	int	off = 0;
	for( int i=0; i<nDim; i++ ) {
		if( index[i] < 0 || index[i] >= dims[i] )
			return -1;
		off += index[i]*indexOffsets[i];
	}
	
	return off;
}


void
cellArray::getState( int index[], cellState &s, int &d )
{
	int	off = offset( index );
	if( off < 0 ) {
		s = csOutside;
		d = -1;
	} else {
		s = cellState(states[off]);
		d = cellData[off].fillOrder;	// XXX only valid if filled
	}
}


void
cellArray::getStates( int index[], int n, int *relNbors, 
			cellState states[], int values[] )
{
    for( int i=0; i<n; i++, relNbors += nDim ) {
	int	pos[2];
	pos[0] = index[0] + relNbors[0];
	pos[1] = index[1] + relNbors[1];
	
	getState( pos, states[i], values[i] );
    }
}

//
//  perform the given operation on each of the enabled positions
//	The Action calling us has already determined that we want
//	to do something on each of the cells, as indicated by the
//	enabled flags.  So we do not have to make any policy 
//	decisions here.
//
void
cellArray::opPos( cellFunction function, int n, int index[], int *relNbors, 
			float wgts[], u_char *enabled )
{
    for( int i=0; i<n; i++, relNbors += nDim ) {
	if( enabled != NULL && !enabled[i] ) 
	    continue;			// this cell not enabled


	int	pos[2];
	pos[0] = index[0] + relNbors[0];
	pos[1] = index[1] + relNbors[1];

	int	off = offset( pos );
	if( off < 0 ) 
	    continue;			// out of bounds

	if( states[off] == csFilled )
	    continue;			// don't mess with filled ones

	//
	//  find "current" weight, with default values we can
	//	use for other operations
	//
	float	oldWgt = 0.0;			// default weight 
	if( states[off] == csWaiting ) {
	    oldWgt = waitList->getWt( cellData[off].waitIndex );
	}

	float	newWgt;
	switch( function ) {
	    case cfAdd:
		newWgt = oldWgt + wgts[i];
		break;
	    case cfMultiply:
		newWgt = oldWgt * wgts[i];
		break;
	    case cfSet:
		newWgt = wgts[i];
		break;
	}

	if( newWgt > 0.0 ) {
	    //
	    // this is easy - just add data or modify weight if 
	    //	this cell is empty or not
	    //
	    if( states[off] == csWaiting ) {
		waitList->setWt( cellData[off].waitIndex, newWgt );
	    } else {
		cellData[off].waitIndex = waitList->addData( pos, newWgt );
		states[off] = csWaiting;
	    }
	} else {
	    if( states[off] == csWaiting ) {
		// 
		// we have some choices here, we can
		//   (1) ignore this case
		//   (2) set the weight to DBL_MIN (currently the default)
		//   (3) set the state of this cell to csEmpty, in which case 
		//       we can 
		//       (A) remove it from the wait list
		//       (B) leave it in the wait list, by setting its state, 
		// 	  leaving the cellData value alone.

		//   (2)
		waitList->setWt( cellData[off].waitIndex, DBL_MIN );
	    } else {
		//
		//  do nothing, there must be some positive probability
		//	to get on the waiting list
		//
	    }
	}
    }
}



void
cellArray::seed( int index[], double weight )
{
	int	off = offset( index );
	if( off >= 0 && states[off] == csEmpty ) {	// XXX seeds can't 
							// overlap ?? !!
		states[off] = csWaiting;
		cellData[off].waitIndex = waitList->addData( index, weight );
	}
}

#if	0

void
cellArray::add( int index[], double weight )
{
	int	off = offset( index );
	if( off < 0 )
		return;
	if( states[off] == csFilled )
		return;

	if( states[off] == csWaiting ) {
		waitList->add( cellData[off].waitIndex, weight );
	} else {
		if( weight <= 0.0 )
			return;
		cellData[off].waitIndex = waitList->add( index, weight );
		states[off] = csWaiting;
	}
}

#endif


void
cellArray::set( int index[] )
{
	int	off = offset( index );
	if( off >= 0 ) {
		states[off] = csFilled;
		cellData[off].fillOrder = setCntr++;
		// printf( "( %d, %d ) <- %d\n", index[0], index[1], cellData[off].fillOrder );
	}
}

void
cellArray::pick( int index[] )
{
	cellState	s;
	int		d;
	do {
		waitList->pick( index );
		getState( index, s, d );
	} while( s != csWaiting );
	if( printPicks ) {
		printf( "picked [" );
		for( int i=0; i<nDim; i++ ) {
			printf( "%d", index[i] );
			if( i<nDim-1 ) putchar( ',' );
		}
		printf( "]\n" );
	}
	assert( s == csWaiting );
	set( index );
}



