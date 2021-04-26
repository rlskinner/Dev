#ifndef	_Index_h_
#define	_Index_h_

#include 	"Dimensions.h"

#include	<vector>

// 
// Useful typedefs
// (XXX need a single types.h file?)
//
typedef	std::vector<int>			IntVector;
typedef	IntVector::iterator			IntVectorIter;
typedef	IntVector::const_iterator	IntVectorConstIter;

typedef	std::vector<int*>				IntPtrVector;
typedef	IntPtrVector::iterator			IntPtrVectorIter;
typedef	IntPtrVector::const_iterator	IntPtrVectorConstIter;

typedef	std::vector<IntPtrVector>			IntPtrVectorVector;
typedef	IntPtrVectorVector::iterator		IntPtrVectorVectorIter;
typedef	IntPtrVectorVector::const_iterator	IntPtrVectorVectorConstIter;

//
// Class Index is an N-dimensional index into a CellArray
//
class Index
	{
	public:
		Index(Dimensions const& dims); // empty
		Index(int numDims); // empty
// 		Index(int numDims, int values[]); // porting aid for int arrays
		Index(Index const& index); // copy constructor
		Index& operator=(Index const& index); // assignment operator
		~Index();

		// Access Operations
		int numDimensions() const { return m_numDims; }
		void set(int iX, int iY = 0, int iZ = 0, int iW = 0);
		void set(int values[]); // porting aid for int arrays

		// Indexing Operations
		int& operator[](int i);
		int operator[] (int i) const;

		// Arithmetic Operations
		Index& operator+=(Index const& index); // += operator

		// Projections into N Dimensions
		Index project(int numDims) const;

		// std::vector Operations
		std::vector<int>::iterator begin() { return m_indexes; }
		std::vector<int>::iterator end() { return m_indexes+m_numDims; }
		std::vector<int>::const_iterator begin() const { return m_indexes; }
		std::vector<int>::const_iterator end() const { return m_indexes+m_numDims; }

	protected:

	private:
		// Index uses a helper class to speed allocation & deallocation
		int		m_numDims;
		int*	m_indexes;

	}; // class Index


// Index Arithmetic Operations
Index operator+(Index const& a, Index const& b);

//
// Class IndexArray stores Index data efficiently 
//
class IndexArray
	{
	public:
		IndexArray(Dimensions const& dims);

		// Access Operations
		int numDimensions() const { return m_numDims; }
		size_t size() const { return m_numIndexes; }
		void get(int i, Index& index) const;

		// Creation Operations
		void push_back(Index const& index);
		void resize(size_t newSize);
		void reserve(size_t newSize);
		void clear() { m_indexArray.clear(); }

		// Indexing Operations
		// Index operator[](int i) const;

	protected:

	private:
		int					m_numDims;
		int					m_numIndexes;
		std::vector<int>	m_indexArray; // flattened array indexes

	}; // class IndexArray
#endif	// _Index_h_
