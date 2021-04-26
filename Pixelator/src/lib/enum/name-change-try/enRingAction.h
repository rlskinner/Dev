#ifndef	_enRingAction_
#define	_enRingAction_

#include	"enAction.h"

class	ringAction : public enAction {
	int	radius;

	virtual	void	makeNbors();

public:
	ringAction( enWeight *wgt, int rad );

	virtual	void	init( int nDim, int dims[] );
};
	
#endif	/* _enRingAction_ */
