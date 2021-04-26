#include	<stdio.h>
#include	<stdlib.h>
#include	<math.h>
#include	<limits.h>
#include	<assert.h>

#include	<vector>

#include	"CellArray.h"

#include	"Index.h"


RandArray::RandArray( size_t _dataSize )
	{
	m_dataSize = _dataSize;
	m_maxSize = 8;
	m_size = 0;
	m_data = new u_char[m_dataSize*(m_maxSize+1)];
	m_wts = new double[m_maxSize+1];
	m_cumWts = new double[2*(m_maxSize+1)+1];
	for( int i=1; i<=2*m_maxSize; i++ ) 
		m_cumWts[i] = 0.0;

	m_indUsed = 0;
	m_indSize = 8;
	m_inds = new int[m_indSize];

	m_autoUpdate = 1;

	m_printSets = getenv( "TD_PRINT_ARRAY_SETS" ) != NULL;
	}


RandArray::~RandArray()
	{
	delete m_data;
	delete m_wts;
	delete m_cumWts;
	delete m_inds;
	}


//
//  Adjust cummulative weights in the heap, starting at heap index 'hi' and
//  going up.
//
void RandArray::incUpdate( int hi )
	{
	while( hi > 0 ) 
		{
		int left = hi << 1;
		m_cumWts[hi] = m_wts[hi] + m_cumWts[left] + m_cumWts[left+1];
		hi >>= 1;
		}

	}


//
//  Fix cummulative weights in the entire tree.  This is called after numerous
//  modifications to the tree.
//
void RandArray::update()
	{
	int	heap = 2*m_size;
	int	up = heap >> 1;
	while( heap >= 2 ) 
		{
		m_cumWts[up] = m_wts[up] + m_cumWts[heap] + m_cumWts[heap+1];
		heap -= 2;
		up--;
		}
	}


//
// Assert that the heap is valid
//
void RandArray::assertHeap()
	{
#if	0
	//  assert validity of heap
	for( int i=1; i<=m_size; i++ )
		{
		assert( m_cumWts[i] == m_wts[i] + m_cumWts[2*i] + m_cumWts[2*i+1]);
		}
#endif
	}


//
// Add a new data element to the heap with the given weight
//
int RandArray::addData(void *newData, // new data element to add
					   double weight // absolute weighting for the new element
					   )
	{
	int	hi;			// heap index where new cell index goes

	//
	//  see if there are empty indices, 
	//	if so, use one of them
	//
	assertHeap();
	if( m_indUsed > 0 )
		{
		hi = m_inds[--m_indUsed];
		} else {

			//
			//  must add at end, make sure heap is big enough
			//
			if( m_size == m_maxSize )
				{
				m_maxSize *= 2;
				// int	*newData = new int[numDimensions()*(m_maxSize+1)];
				// bcopy( m_data, newData, numDimensions()*(m_size+1)*sizeof(int) );
				// delete m_data;
				// m_data = newData;
				m_data = (u_char*)realloc( m_data, m_dataSize*(m_maxSize+1) );

				// double	*newW = new double[m_maxSize+1];
				// bcopy( m_wts, newW, (m_size+1)*sizeof(double) );
				// delete m_wts;
				// m_wts = newW;
				m_wts = (double*)realloc( m_wts, (m_maxSize+1)*sizeof(double) );

				// maintain extra large heap
				// double	*newCw = new double[2*(m_maxSize+1)+1];
				// bcopy( m_cumWts, newCw, (m_size+1)*sizeof(double) );
				// for( int i=m_size+1; i<=2*m_maxSize; i++ )
				// {
				// newCw[i] = 0.0;
				// }
				// delete m_cumWts;
				// m_cumWts = newCw;
				m_cumWts = (double*)realloc( m_cumWts, 2*(m_maxSize+1)*sizeof(double) );
				}
			m_size++;

			// maintain extra large heap
			m_cumWts[2*m_size] = 0.0;
			m_cumWts[2*m_size+1] = 0.0;

			hi = m_size;
		}

	bcopy( newData, &m_data[hi*m_dataSize], m_dataSize ); 

	//
	//  add this weight to heap
	//
	setWt( hi, weight );		// XXX did I want to add?

	assertHeap();
	return hi;
	}



//
//  SET the weight at the given heap index.
//  The weight is not added
//
void RandArray::setWt(int heap, // heap index to be set
					  double wt // new index weight, wt > 0
					  ) 
	{
	assert( wt > 0.0 );
	m_wts[heap] = wt;
	if( m_printSets )
		printf( "RandArray::setWt( %d, %g )\n", heap, wt );
	if( m_autoUpdate )
		incUpdate( heap );
	}


//
//  Clear the weight at the given heap index so that this item can be "removed"
//
void RandArray::clearWt(int heap // heap index to be cleared
						)
	{
	m_wts[heap] = 0.0;
	if( m_autoUpdate )
		incUpdate( heap );
	}


//
// Pick one element and return its data
//
void RandArray::pick(void *pickData // out: data about the element picked
					 )
	{
	//
	//  find random number 0.0 <= r <= total weight
	//
	double	pickRand = randomInRange(0.0, getTotalWt());

	//
	//  traverse down the tree, finding where pickRand goes
	//
	int	li = 1;				// logical index
	while( 1 ) // until we break
		{
		int left = 2*li;		// logical, again

		if( pickRand < m_cumWts[left] )
			{
			li = left;		// go to left subtree
			}
		else
			{
			pickRand -= m_cumWts[left];// this many fewer to deal with
			int right = left+1;
			if( pickRand < m_cumWts[right] )
				{
				li = right;	// go to right subtree
				} 
			else 
				{
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
	bcopy( &m_data[li*m_dataSize], pickData, m_dataSize );
	if( m_indUsed == m_indSize )
		{
		m_indSize *= 2;
		m_inds = (int*)realloc( m_inds, m_indSize*sizeof(int) );
		}
	m_inds[m_indUsed++] = li;
	clearWt( li );
	}


///////////////////////////////////////////////////////////////////////
//
//  class CellArray

//
// Create a new cell array of the given dimensions
//
// NOTE: CellArray is intended for single-use.  If you wish to recompute a
// sequence, allocate a new instance.  (I'm really too lazy to reinitialize
// cleanly.)
CellArray::CellArray(Dimensions const& dims, 
					 SavePickSequence savePicks
					)
	: m_dims(dims)
	, m_indexOffsets(0)
	, m_states(0)
	, m_cellData(0)
	, m_setCntr(0)
	, m_totalCount(0)
	, m_waitList(0)
	, m_savePickSequence(savePicks)
	, m_pickSequence(dims)
	{
	m_indexOffsets = new int[numDimensions()];

	m_totalCount = 1;
	for( int i=0; i<numDimensions(); i++ )
		{
		m_indexOffsets[i] = m_totalCount;// must be *before* total increased
		m_totalCount *= m_dims[i];
		}

	m_states = new char[m_totalCount];
	m_cellData = new CellDataUnion[m_totalCount];
	for(int i=0; i<m_totalCount; i++ )
		{
		m_states[i] = csEmpty;
		// m_cellData[i] = 0;		// so add() can just accumulate
		}

	m_waitList = new RandArray(sizeof(int));

	// set the pick sequence array size
	m_pickSequence.reserve(m_totalCount);

	m_printPicks = getenv( "TD_PRINT_PICKS" ) != NULL;
	}


CellArray::~CellArray()
	{
	delete m_indexOffsets;
	delete m_states;
	delete m_cellData;
	delete m_waitList;
	}


//
//  Initialize the cell array for the given PixelEnumerator
//
void CellArray::init()
	{
	}



//
// Return the number of cells waiting to be picked.
//
int CellArray::numWaiting()
	{
	return m_waitList->numWaiting();
	}


//
// Print text version of the cell array (2D only)
//
void
CellArray::print()
	{
	if( numDimensions() != 2 ) 
		{
		printf( "sorry, can't print %dD version", numDimensions() );
		}

	for( int i=0; i<m_dims[0]; i++ ) 
		{
		printf( "%4d", i );
		}
	printf( "\n" );

	for( int j=m_dims[1]-1; j>=0; j-- ) 
		{
		printf( "%3d ", j );
		for( int i=0; i<m_dims[0]; i++ ) 
			{
			Index ii(numDimensions());
			ii.set(i, j);

			CellState	s;
			int		d;
			getState( ii, s, d );
			switch( s ) 
				{
				case csEmpty:
					printf( "   ." );
					break;
				case csWaiting:
					printf( "%4d", -d );
					break;
				case csFilled:
					printf( "%4d", d );
					break;
				case csOutside:
					break;
				}
			}
		printf( "\n" );
		}
	}



//
//  Convert the given N-D cell index into a 1D array index (into the
//  internal cell array)
//
int CellArray::offset(Index const& index // cell index
					  )
	{
	//
	//  unrolled loop for most common cases
	//
	if( numDimensions() == 2 )
		{
		int i0 = index[0];
		int i1 = index[1];
		if( i0 < 0 || i0 >= m_dims[0] ||
			i1 < 0 || i1 >= m_dims[1] )
			return -1;
		return i0*m_indexOffsets[0] + 
			i1*m_indexOffsets[1];
		}

	if( numDimensions() == 3 )
		{
		int i0 = index[0];
		int i1 = index[1];
		int i2 = index[2];
		if( i0 < 0 || i0 >= m_dims[0] ||
			i1 < 0 || i1 >= m_dims[1] ||
			i2 < 0 || i2 >= m_dims[2] )
			return -1;
		return i0*m_indexOffsets[0] + 
			i1*m_indexOffsets[1] + 
			i2*m_indexOffsets[2];
		}

	//
	//  the most general case
	//
	int	off = 0;
	for( int i=0; i<numDimensions(); i++ ) 
		{
		int ii = index[i];
		if( ii < 0 || ii >= m_dims[i] )
			return -1;
		off += ii*m_indexOffsets[i];
		}

	return off;
	}


//
//  Convert the given 1D array index (into the internal cell array) into an
//  N-D cell index 
//
Index CellArray::offsetToIndex(int offset // 1D internal cell array index
							  )
	{
	assert(0 <= offset && offset < m_totalCount);

	Index index(numDimensions());

	//
	//  unrolled loop for most common cases
	//
	if( numDimensions() == 2 )
		{
		int i0 = index[0];
		int i1 = index[1];
		i1 = offset / m_indexOffsets[1];
		i0 = offset % m_indexOffsets[1];
		}

	if( numDimensions() == 3 )
		{
		index[2] = offset / m_indexOffsets[2];
		offset %= m_indexOffsets[2];
		index[1] = offset / m_indexOffsets[1];
		index[0] = offset % m_indexOffsets[1];
		}

	//
	//  the most general case
	//
	for( int i=numDimensions()-1; i>=0; --i)
		{
		index[i] = offset / m_indexOffsets[i];
		offset %= m_indexOffsets[i];
		}

	return index;
	}


//
// Get the cell state and value for the given cell index
//
void CellArray::getState(Index const& index, // index of the cell to query
						 CellState &s, // out: state of the cell
						 int &d // out: value of the cell
						 )
	{
	int	off = offset( index );
	if( off < 0 )
		{
		s = csOutside;
		d = -1;
		}
	else
		{
		s = CellState(m_states[off]);
		d = m_cellData[off].fillOrder;	// XXX only valid if filled
		}
	}


//
// Get the cell states and values for a group of cells relative to the given
// cell index
//
void CellArray::getStates(Index const& index, // index of the cell to query
						  IndexArray const& relNbors, // array of indexes relative to index
						  CellStateVector& states, // out: state of each cell
						  std::vector<int>& values // out: value of each cell
						 )
	{
	states.resize(relNbors.size());
	values.resize(relNbors.size());

	Index	pos(index.numDimensions());
	for(size_t i=0; i<relNbors.size(); i++)
		{
		relNbors.get(i, pos);
		pos += index;
		getState(pos, states[i], values[i]);
		}
	}

//
//  perform the given operation on each of the enabled positions
//	The Action calling us has already determined that we want
//	to do something on each of the cells, as indicated by the
//	enabled flags.  So we do not have to make any policy 
//	decisions here.
//
//  XXX need a version of this that just operates on one cell?
void CellArray::opPos(CellFunction function, // the "function" to perform
					  Index const& index, // index of the 'picked' cell
					  IndexArray const& relNbors, // array of positions relative to index
					  std::vector<double>& wgts, // weights to be applied, depending on function
					  std::vector<bool>& enabled // array of enable flags for each cell
					 )
	{
	Index	pos(index.numDimensions());
	for(size_t i=0; i<relNbors.size(); ++i)
		{
		if(i < enabled.size() // enabled array not empty -> use it for flags
		   && !enabled[i])		// this cell not enabled 
			continue;

		relNbors.get(i, pos);
		pos += index;

		int	off = offset( pos );
		if( off < 0 ) 
			continue;			// out of bounds

		if( m_states[off] == csFilled )
			continue;			// don't mess with filled ones

		//
		//  find "current" weight, with default values we can
		//	use for other operations
		//
		double	oldWgt = 0.0;			// default weight 
		if( m_states[off] == csWaiting )
			{
			oldWgt = m_waitList->getWt( m_cellData[off].waitIndex );
			}

		double	newWgt;
		switch( function )
			{
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

		if( newWgt > 0.0 )
			{
			//
			// this is easy - just add data or modify weight if 
			//	this cell is empty or not
			//
			if( m_states[off] == csWaiting )
				{
				m_waitList->setWt( m_cellData[off].waitIndex, newWgt );
				}
			else
				{
				m_cellData[off].waitIndex = m_waitList->addData( &off, newWgt );
				m_states[off] = csWaiting;
				}
			}
		else
			{
			if( m_states[off] == csWaiting )
				{
				// 
				// we have some choices here, we can
				//   (1) ignore this case
				//   (2) set the weight to DBL_MIN (currently the default)
				//   (3) set the state of this cell to csEmpty, in which case 
				//       we can 
				//       (A) remove it from the wait list
				//       (B) leave it in the wait list, by setting its state, 
				// 	  leaving the m_cellData value alone.

				//   (2)
				m_waitList->setWt( m_cellData[off].waitIndex, DBL_MIN );
				}
			else
				{
				//
				//  do nothing, there must be some positive probability
				//	to get on the waiting list
				//
				}
			}
		}
	}



//
//  Seed the cell at the given index with the given weight
//
void CellArray::seed(Index const& index, // index of cell to seed
					 double weight // weight to give to the cell
					 )
	{
	int	off = offset( index );
	if( off >= 0 && m_states[off] == csEmpty )
		{	// XXX seeds can't 
		// overlap ?? !!
		m_states[off] = csWaiting;
		m_cellData[off].waitIndex = m_waitList->addData( &off, weight );
		}
	}

#if	0

	void
CellArray::add( int index[], double weight )
	{
	int	off = offset( index );
	if( off < 0 )
		return;
	if( m_states[off] == csFilled )
		return;

	if( m_states[off] == csWaiting )
		{
		m_waitList->add( m_cellData[off].waitIndex, weight );
		} else {
			if( weight <= 0.0 )
				return;
			m_cellData[off].waitIndex = m_waitList->add( index, weight );
			m_states[off] = csWaiting;
		}
	}

#endif


//
//  Set (pick, choose, fill) the cell at the given index.  The cell is
//  automatically assigned a sequential value.
//
void CellArray::set(Index const& index // index of cell to set
				   )
	{
	int	off = offset( index );
	if( off >= 0 )
		{
		m_states[off] = csFilled;
		m_cellData[off].fillOrder = m_setCntr++;
		// printf( "( %d, %d ) <- %d\n", index[0], index[1], m_cellData[off].fillOrder );
		}
	}


// 
// Pick one cell and return its index
//
void CellArray::pick(Index& index // out: index of the cell picked
					 )
	{
	CellState	s;
	int		d;
	int 	off;
	do {
		m_waitList->pick( &off );
		index = offsetToIndex(off);
		getState( index, s, d );
	} while( s != csWaiting );

	if(cSavePickSequence == m_savePickSequence)
		{
		m_pickSequence.push_back(index);
		}

	if( m_printPicks )
		{
		printf( "picked [" );
		for( int i=0; i<numDimensions(); i++ )
			{
			printf( "%d", index[i] );
			if( i<numDimensions()-1 ) putchar( ',' );
			}
		printf( "]\n" );
		}

	assert( s == csWaiting );
	set( index );
	}




#if	0
// Functions formerly in PixelEnumerator, but that should really apply to
// CellArray (maybe)

loadCmap = FALSE;
cmapFilename = NULL;
writeFile = FALSE;
writeFilename = NULL;

#if	IMAGE_SUPPORT
fitZoom	*fz = fitImages;
while( fz != NULL ) 
	{
	ilRotZoomImg    *rz = (ilRotZoomImg*)fz->img;
	rz->sizeToFit( m_dims[0], m_dims[1] );
	fz = fz->next;
	}
#endif

void	PixelEnumerator::addZoomToFit( ilImage *img )
	{
	fitZoom	*fz = new fitZoom( img );
	fz->next = fitImages;
	fitImages = fz;
	}

void PixelEnumerator::loadColormap( char *file )
	{
	loadCmap = 1;
	cmapFilename = strdup( file );
	}


void PixelEnumerator::setWriteImage( char *file, char * /*type */ )
	{
	writeFile = 1;
	writeFilename = strdup( file );
	}


#if	IMAGE_SUPPORT
void PixelEnumerator::writeImage()
	{
	if( !writeFile )
		return;

	iflFileConfig cfg( new iflSize( m_dims[0], m_dims[1], 1 ), 
					   iflLong, iflInterleaved, iflRGBPalette );
	ilFileImg 	*img = new ilFileImg( writeFilename, NULL, &cfg );

	long	*buf = new long[m_dims[0]];
	for( int j=0; j<m_dims[1]; j++ )
		{
		for( int i=0; i<m_dims[0]; i++ )
			{
			if( cells->m_states[i+j*m_dims[0]] == csFilled )
				{
				buf[i] = cells->m_cellData[i+j*m_dims[0]].fillOrder;
				} else {
					buf[i] = 0;
				}
			}
		img->setTile( 0, j, m_dims[0], j+1, buf );
		}
	delete img;
	delete buf;
	}
#endif


#endif
