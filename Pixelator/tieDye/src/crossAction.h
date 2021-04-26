#ifndef	_crossAction_
#define	_crossAction_

#include	"action.h"

class	crossAction : public action {
	int	size;

	virtual	void	makeNbors();

public:
	crossAction( weight *wgt, int sz )
		: action( wgt )
		{ size = sz;  }

	virtual	void	init( int nDim, int dims[] );
};
	
#endif	/* _crossAction_ */
