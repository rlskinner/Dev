#include	<stdio.h>
#include	<stdlib.h>
#include	<math.h>
#include	<limits.h>
#include	<assert.h>
#include	<bstring.h>

#include	"cellArray.h"


randArray::randArray( int nd )
{
	nDim = nd;
	maxSize = 8;
	size = 0;
	data = new int[nDim*(maxSize+1)];
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
randArray::add( int index[], double weight )
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
			data = (int*)realloc( data, nDim*(maxSize+1)*sizeof(int) );
	
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

	bcopy( index, &data[nDim*hi], nDim*sizeof(int) ); 

	//
	//  add this weight to heap
	//
	setWt( hi, weight );		// XXX did I want to add?

	assertHeap();
	return hi;
}


void
randArray::add( int heap, double w )
{
    setWt( heap, wts[heap]+w );
}



//
//  SET weight, do not add
//	wt <= 0.0 is NOT allowed
//
void
randArray::setWt( int heap, double wt ) 
{
    if( wt <= 0.0 ) {
	if( printSets )
	    printf( "randArray::setWt( %d, %g ), adjusted\n", heap, wt );
	wt = DBL_MIN;
    }
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
randArray::pick( int index[] )
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
	bcopy( &data[nDim*li], index, nDim*sizeof(int) );
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
	offsets = new int[nDim];

	totalCount = 1;
	for( int i=0; i<nd; i++ ) {
		dims[i] = d[i];
		offsets[i] = totalCount;// must be *before* total increased
		totalCount *= dims[i];
	}

	states = new char[totalCount];
	data = new int[totalCount];
	for( i=0; i<totalCount; i++ ) {
		states[i] = csEmpty;
		data[i] = 0;		// so add() can just accumulate
	}

	waitList = new randArray( nDim );

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
		return index[0]*offsets[0] + 
		       index[1]*offsets[1];
	}

	if( nDim == 3 ) {
		if( index[0] < 0 || index[0] >= dims[0] ||
		    index[1] < 0 || index[1] >= dims[1] ||
		    index[2] < 0 || index[2] >= dims[2] )
			return -1;
		return index[0]*offsets[0] + 
		       index[1]*offsets[1] + 
		       index[2]*offsets[2];
	}

	//
	//  the most general case
	//
	int	off = 0;
	for( int i=0; i<nDim; i++ ) {
		if( index[i] < 0 || index[i] >= dims[i] )
			return -1;
		off += index[i]*offsets[i];
	}
	
	return off;
}


void
cellArray::getState( int index[], cellState &s, int &d )
{
	int	off = offset( index );
	if( off < 0 ) {
		s = csFilled;
	} else {
		s = cellState(states[off]);
		d = data[off];
	}
}


void
cellArray::seed( int index[], double weight )
{
	int	off = offset( index );
	if( off >= 0 && states[off] == csEmpty ) {
		states[off] = csWaiting;
		data[off] = waitList->add( index, weight );
	}
}


void
cellArray::add( int index[], double weight )
{
	int	off = offset( index );
	if( off < 0 )
		return;
	if( states[off] == csFilled )
		return;

	if( states[off] == csWaiting ) {
		waitList->add( data[off], weight );
	} else {
		if( weight <= 0.0 )
			return;
		data[off] = waitList->add( index, weight );
		states[off] = csWaiting;
	}
}


void
cellArray::set( int index[] )
{
	int	off = offset( index );
	if( off >= 0 ) {
		states[off] = csFilled;
		data[off] = setCntr++;
		// printf( "( %d, %d ) <- %d\n", index[0], index[1], data[off] );
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



