#ifndef	_PixelEnumerator_h_
#define	_PixelEnumerator_h_
//
//  PixelEnumerator application class
//

#include	"action.h"
#include	"cellArray.h"
#include	"Index.h"
#include	"seed.h"

// #include	"glCellArray.h"

class	PixelEnumerator	
	{
	protected:
		// options	*ops;
		Seed	*m_seeds;
		Action	*m_actions;
		CellArray	*m_cells;
		Dimensions	m_dims;

		void	doActions(Index& index);

	public:
		PixelEnumerator();
		virtual	~PixelEnumerator();

		int numDimensions() { return m_dims.numDimensions(); }

		void	init(CellArray *cellArray);
		virtual	void	setCellArray(CellArray *cellArray);
		virtual	void	pick(Index& index);
		// virtual Index pick() // 1
		// virtual Index[] pick(int)

		void	addSeed( Seed *s )      { s->m_next = m_seeds;  m_seeds = s; }
		void    addAction( Action *a )  { a->m_next = m_actions;  m_actions = a; }

		void	setDims(Dimensions const& dims);

		// should really split out the CellArray instance in order to
		// 	* query it's state:
		// 		* # picked
		// 		* # not picked
		// 		* the picked list? (XXX may be too big to always store)
		// 	* change CellArray definition (e.g. size) without redefining
		// 	PixelEnumerator
		// 	* Seems like PixelEnumerator and CellArray don't need to be
		// 	abstract.  Surely default actions are useful in many cases...
		// 	* sharing issues -- CellArray may be very big -- need to be careful
		// 	about resource management.
		// 	* CellArray should optionally remember the sequence of
		// 	indexes.  Optionally, because the list may also be very big.

	};

#endif	// _PixelEnumerator_h_
