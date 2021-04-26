#ifndef	_newEdgeAction_
#define	_newEdgeAction_

#include	<stdio.h>

#include	"action.h"

class	newEdgeAction : public action {
protected:
	double	wtGain;

	virtual	void	makeNbors();

public:
	newEdgeAction( double wg, double wgt = 1.0 ) 
		: action( wgt )
		{ wtGain = wg; }

	virtual void	doAction( cellArray *cells, int index[] );
};
	
#endif	/* _newEdgeAction_ */
