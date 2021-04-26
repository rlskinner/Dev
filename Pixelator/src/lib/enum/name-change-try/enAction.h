#ifndef	_enAction_
#define	_enAction_

#include	<stdio.h>
#include	<sys/types.h>

#include	"enCellArray.h"
#include	"enWeight.h"

#ifndef	TRUE
#define	TRUE	1
#define	FALSE	0
#endif


class	enAction {
protected:
	int	_nDim;
	int*	_dims;
	enWeight  *_wgt;

	//
	//  actions keep a list of relative positions to affect 
	//	and their relative weights
	//
	int	_numNbors;		// # of cells this action affects
	int	*_nbors;			// (relative) list of cells affected 
	float	*_relNborWgts;		// relative wgts of affected cells
	float	*_newNborWgts;		// temp buffer for resultant weights
	u_char	*_nborEnable;		// enable flags, depending on classify
	CellState	*_nborStates;	// cell states for selection
	int	*_nborValues;		// cell values for selection

	void	setNumNbors( int n );
	virtual	void	makeNbors() = 0;
	void	setConstWgts()	{ delete _relNborWgts; relNborWgts = NULL; }

	//
	//  select weights depending on numerical properties
	//
	enActionWeight::ActionWeightSelect	selectWgts;
	void	selectWgtValues();

	//
	//  select Positions depending on cell states
	//
	int	selectStates;		// bit OR of states
	void	selectCellStates( enCellArray *cells, int index[] );

	// cellState	addState;	// if == csEmpty, cell must be empty
					// to add in doAction;

	//
	//  function we want performed on cell's weight
	//	does the MULTIPLY function imply selectStates == csWaiting?
	//
	CellFunction	_function;

public:
	//
	//  define classifications we can do on sets of weights
	//
	enum	ActionWeightSelect {
	    awAll,			// take them all
	    awMax,			// take only Max
	    awMin,			// or Min
	    awPositive,			// only positive values
	    awNegative,			// only negative values
	};

	enAction	*next;
	enAction( enWeight *_wgt );
	virtual ~enAction();

	virtual	void	init( int nDim, int dims[] );
	virtual void	doAction( enCellArray *cells, int index[] );

	virtual	void	setWeightSelection( enActionWeightSelect aws )
				{ selectWgts = aws; }

	virtual	void	setStateSelection( int sss )
				{ selectStates = sss; }

	virtual	void	setWeightFunction( CellFunction f )
				{ function = f; }
};
	
#endif	/* _enAction_ */
