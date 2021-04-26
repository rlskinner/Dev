#include "Index.h"

#include	<algorithm>

#include	<assert.h>

using namespace std;

//////////////////////////////////////////////////////////////////////////
//
// Class IndexAllocator
//
// Helper class for fast Index allocation:  cache allocation of small 
// integer arrays and never release them.
//
class IndexAllocator
	{
	public:
		IndexAllocator();
		~IndexAllocator();

		int* newIndexes(int size);
		void deleteIndexes(int size, int* indexes);

	private:
		IntPtrVectorVector m_indexPtrVectors; // pointers available
	}; // class IndexAllocator

static IndexAllocator s_indexAllocator;


IndexAllocator::IndexAllocator()
	: m_indexPtrVectors() // initially empty
	{
	}


IndexAllocator::~IndexAllocator()
	{
	}


int* IndexAllocator::newIndexes(int size)
	{
	// make sure we have an array for this size
	if(int(m_indexPtrVectors.size()) < size+1)
		{
		m_indexPtrVectors.resize(size+1);
		}

	// get the vector of index points for this size array
	IntPtrVector &indexPtrs = m_indexPtrVectors[size];

	// is there an index pointer we can spare
	if(indexPtrs.size() > 0)
		{
		int* newIndex = indexPtrs.back();
		indexPtrs.pop_back();
		return newIndex;
		}

	// return a new index pointer
	return new int[size];
	}


void IndexAllocator::deleteIndexes(int size, int* indexes)
	{
	assert((m_indexPtrVectors.size()) >= size+1); // newIndexes resized vector
	m_indexPtrVectors[size].push_back(indexes);
	}


//////////////////////////////////////////////////////////////////////////
//
// Class Index
//

// Constructors
Index::Index(int numDims)
	: m_numDims(numDims)
	, m_indexes(s_indexAllocator.newIndexes(numDims))
	{
	}


Index::Index(Dimensions const& dims)
	: m_numDims(dims.numDimensions())
	, m_indexes(s_indexAllocator.newIndexes(dims.numDimensions()))
	{
	}


Index::Index(Index const& other)
	: m_numDims(other.m_numDims)
	, m_indexes(s_indexAllocator.newIndexes(other.numDimensions()))
	{
	copy(other.begin(), other.end(), m_indexes);
	}


#if	0
// porting aid for int arrays
Index::Index(int numDims, int values[])
	: m_indexes(s_indexAllocator.newIndexes(numDims)
	{
	set(values);
	}
#endif


Index& Index::operator=(Index const& other)
	{
	assert(numDimensions() == other.numDimensions());
	copy(other.begin(), other.end(), m_indexes);
	return *this;
	}


	Index::~Index()
	{
	s_indexAllocator.deleteIndexes(m_numDims, m_indexes);
	m_indexes = 0;
	m_numDims = 0;
	}

void Index::set(int iX, int iY, int iZ, int iW)
	{
	switch(numDimensions())
		{
		case 4: m_indexes[3] = iW;
		case 3: m_indexes[2] = iZ;
		case 2: m_indexes[1] = iY;
		case 1: m_indexes[0] = iX;
		}
	}


// porting aid for int arrays
void Index::set(int values[])
	{
	copy(values, values+numDimensions(), m_indexes);
	}


// Access Operations

// Indexing Operations
int& Index::operator[](int i)
	{
	assert(0 <= i && i < numDimensions());
	return m_indexes[i];
	}


int Index::operator[](int i) const
	{
	assert(0 <= i && i < numDimensions());
	return m_indexes[i];
	}


// Arithmetic Operations
Index& Index::operator+=(Index const& other)
	{
	int N = numDimensions();
	assert(N == other.numDimensions());

	for(int i=0; i<N; ++i)
		{
		m_indexes[i] += other.m_indexes[i];
		}

	return *this;
	}


// Projections from N to M Dimensions
Index Index::project(int numDims) const
	{
	Index index(numDims);
	for(int i=0; i<numDims; ++i)
		{
		if(i < numDimensions())
			{
			index.m_indexes[i] = m_indexes[i];
			}
		else
			{
			index.m_indexes[i] = 0;
			}
		}

	return index;
	}


Index operator+(Index const& a, Index const& b)
	{
	assert(a.numDimensions() == b.numDimensions());

	Index sum(a.numDimensions());
	for(int i=0; i<a.numDimensions(); ++i)
		{
		sum[i] = a[i] + b[i];
		}

	return sum;
	}


//////////////////////////////////////////////////////////////////////////
//
// Class IndexArray
//

// Constructors
IndexArray::IndexArray(Dimensions const& dims)
	: m_numDims(dims.numDimensions())
	, m_numIndexes(0)
	, m_indexArray()
	{
	}



// Access Operations


void IndexArray::get(int i, Index& index) const
	{
	assert(0 <= i && i < size());
	assert(index.numDimensions() == numDimensions());

	int indexInternal = i*numDimensions();
	for(int ii=0; ii<numDimensions(); ++ii)
		{
		index[ii] = m_indexArray[indexInternal+ii];
		}
	}


// Creation Operations
void IndexArray::push_back(Index const& index)
	{
	if(numDimensions() == index.numDimensions())
		{
		m_indexArray.insert(m_indexArray.end(), index.begin(), index.end());
		}
	else
		{
		Index effectiveIndex = index.project(m_numDims);
		m_indexArray.insert(m_indexArray.end(), effectiveIndex.begin(), effectiveIndex.end());
		}
	++m_numIndexes;
	}


void IndexArray::resize(size_t newSize)
	{
	m_numIndexes = newSize;
	m_indexArray.resize(m_numDims*m_numIndexes);
	}


void IndexArray::reserve(size_t newSize)
	{
	m_indexArray.reserve(m_numDims*newSize);
	}


// Indexing Operations
// XXX too expensive, use get accessor 
// Index IndexArray::operator[](int i) const
// 	{
// 	Index index(numDimensions());
// 	get(i, index);
// 	return index;
// 	}



