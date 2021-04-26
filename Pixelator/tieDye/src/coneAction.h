#ifndef	_coneAction_
#define	_coneAction_

#include	"action.h"

class	coneAction : public action {
	int	radius;

	virtual	void	makeNbors();

public:
	coneAction( weight *wgt, int rad )
		: action( wgt )
		{ radius = rad; }

	virtual	void	init( int nDim, int dims[] );
};
	
#endif	/* _coneAction_ */
