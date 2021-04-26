#ifndef	_action_
#define	_action_

#include	<stdio.h>

#include	"cellArray.h"
#include	"weight.h"

class	action {
protected:
	int	nDim;
	int*	dims;
	weight  *wgt;

	//
	//  actions keep a list of relative positions to affect 
	//	and their relative weights
	//
	int	numNbors;
	int	*nbors;
	float	*nborWgts;
	void	setNumNbors( int n );
	virtual	void	makeNbors() = 0;
	void	setConstWgts()	{ delete nborWgts; nborWgts = NULL; }

	cellState	addState;	// if == csEmpty, cell must be empty
					// to add in doAction;

public:
	action	*next;
	action( weight *_wgt );

	virtual	void	init( int nDim, int dims[] );
	virtual void	doAction( cellArray *cells, int index[] );
};
	
#endif	/* _action_ */
