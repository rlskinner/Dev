#ifndef	_action_
#define	_action_

#include	<stdio.h>
#include	<sys/types.h>

#include	"cellArray.h"
#include	"weight.h"

#ifndef	TRUE
#define	TRUE	1
#define	FALSE	0
#endif


//
//  define classifications we can do on sets of weights
//
enum	actionWeightSelect {
	    awAll,			// take them all
	    awMax,			// take only Max
	    awMin,			// or Min
	    awPositive,			// only positive values
	    awNegative,			// only negative values
	};

class	action {
protected:
	int	nDim;
	int*	dims;
	weight  *wgt;

	//
	//  actions keep a list of relative positions to affect 
	//	and their relative weights
	//
	int	numNbors;		// # of cells this action affects
	int	*nbors;			// (relative) list of cells affected 
	float	*relNborWgts;		// relative wgts of affected cells
	float	*newNborWgts;		// temp buffer for resultant weights
	u_char	*nborEnable;		// enable flags, depending on classify
	cellState	*nborStates;	// cell states for selection
	int	*nborValues;		// cell values for selection
	void	setNumNbors( int n );
	virtual	void	makeNbors() = 0;
	void	setConstWgts()	{ delete relNborWgts; relNborWgts = NULL; }

	//
	//  select weights depending on numerical properties
	//
	actionWeightSelect	selectWgts;
	void	selectWgtValues();

	//
	//  select Positions depending on cell states
	//
	int	selectStates;		// bit OR of states
	void	selectCellStates( cellArray *cells, int index[] );

	// cellState	addState;	// if == csEmpty, cell must be empty
					// to add in doAction;

	//
	//  function we want performed on cell's weight
	//	does the MULTIPLY function imply selectStates == csWaiting?
	//
	cellFunction	function;

public:
	action	*next;
	action( weight *_wgt );
	virtual ~action();

	virtual	void	init( int nDim, int dims[] );
	virtual void	doAction( cellArray *cells, int index[] );

	virtual	void	setWeightSelection( actionWeightSelect aws )
				{ selectWgts = aws; }

	virtual	void	setStateSelection( int sss )
				{ selectStates = sss; }

	virtual	void	setWeightFunction( cellFunction f )
				{ function = f; }
};
	
#endif	/* _action_ */
