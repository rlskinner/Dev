#ifndef _Dimensions_h_
#define _Dimensions_h_

#include	<vector>

// 
// Class Dimensions defines N-dimensional dimensions for a CellArray
// 	It is a simple wrapper around an integer array, with convenience
// 	functions for manipulating indexes into the N-dim space.
//
// XXX we could define very a compact "offset" indexas a single intteger
// that we could convert into nice int[] indexes...
//

enum DimensionIndex { X, Y, Z, W };

class Dimensions
	{
	public:
		// Constructors
		Dimensions() : m_dims() {} // XXX remove this if possible
		Dimensions(int sizeX, int sizeY);
		Dimensions(int sizeX, int sizeY, int sizeZ);
		Dimensions(int sizeX, int sizeY, int sizeZ, int sizeW); // who knows?

		// Access Functions
		int numDimensions() const { return m_numDims; }
		int size(int dim) const;
		int totalSize() const; // product of dimensions

		int operator[](int index) const { return size(index); }

	protected:

	private:
		// Dimensions is a simple wrapper around an integer array
		int					m_numDims;
		std::vector<int>	m_dims;

	}; // class Dimensions

#endif // _Dimensions_h_
