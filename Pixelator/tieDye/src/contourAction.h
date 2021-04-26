#ifndef	_contourAction_
#define	_contourAction_

#include	"action.h"

class	contourAction : public action {
	weight	*primary;

	virtual	void	makeNbors();

public:
	contourAction( weight *_wgt )
		: action( _wgt )
		{ }

	virtual	void	init( int nDim, int dims[] );
	virtual void	doAction( cellArray *cells, int index[] );
};
	
#endif	/* _contourAction_ */
