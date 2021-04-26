#include	"Dimensions.h"

#include	<assert.h>

// 
// Class Dimensions defines N-dimensional dimensions for a CellArray
// 	It is a simple wrapper around an integer array, with convenience
// 	functions for manipulating indexes into the N-dim space.
//
// XXX we could define very a compact "offset" indexas a single intteger
// that we could convert into nice int[] indexes...
//
		// Constructors
Dimensions::Dimensions(int sizeX,
					   int sizeY
					  )
	: m_numDims(2)
	, m_dims(2)
	{
	assert(sizeX > 0);
	assert(sizeY > 0);

	m_dims[0] = sizeX;
	m_dims[1] = sizeY;

	assert(totalSize() < UINT_MAX);
	}


Dimensions::Dimensions(int sizeX,
					   int sizeY,
					   int sizeZ
					  )
	: m_numDims(3)
	, m_dims(3)
	{
	assert(sizeX > 0);
	assert(sizeY > 0);
	assert(sizeZ > 0);

	m_dims[0] = sizeX;
	m_dims[1] = sizeY;
	m_dims[2] = sizeZ;

	assert(totalSize() < UINT_MAX);
	}


Dimensions::Dimensions(int sizeX,
					   int sizeY,
					   int sizeZ,
					   int sizeW
					  )
	: m_numDims(4)
	, m_dims(4)
	{
	assert(sizeX > 0);
	assert(sizeY > 0);
	assert(sizeZ > 0);
	assert(sizeW > 0);

	m_dims[0] = sizeX;
	m_dims[1] = sizeY;
	m_dims[2] = sizeZ;
	m_dims[3] = sizeW;

	assert(totalSize() < UINT_MAX);
	}


int Dimensions::size(int dim
					) const
	{
	assert(0 <= dim && dim < numDimensions());
	return m_dims[dim];
	}


int Dimensions::totalSize() const
	{
	int totSize = size(0);
	for(int i = 1; i<numDimensions(); ++i)
		{
		totSize *= size(i);
		}

	return totSize;
	}


