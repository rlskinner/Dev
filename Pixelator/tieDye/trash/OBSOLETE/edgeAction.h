#ifndef	_edgeAction_
#define	_edgeAction_

#include	<stdio.h>

#include	"action.h"

class	edgeAction : public action {
protected:
	virtual	void	makeNbors();
public:
	edgeAction( weight *wgt ) 
		: action( wgt )
		{}

};
	
#endif	/* _edgeAction_ */
