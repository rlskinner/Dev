#ifndef	_ringAction_
#define	_ringAction_

#include	"action.h"

class	ringAction : public action {
	int	radius;

	virtual	void	makeNbors();

public:
	ringAction( weight *wgt, int rad );

	virtual	void	init( int nDim, int dims[] );
};
	
#endif	/* _ringAction_ */
