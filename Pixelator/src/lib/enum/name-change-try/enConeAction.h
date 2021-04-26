#ifndef	_enConeAction_
#define	_enConeAction_

#include	"enAction.h"

class	enConeAction : public enAction {
protected:
	int	_radius;

	virtual	void	makeNbors();

public:
	enConeAction( enWeight *wgt, int rad )
		: enAction( wgt )
		{ radius = rad; }

	virtual	void	init( int nDim, int dims[] );
};
	
#endif	/* _enConeAction_ */
