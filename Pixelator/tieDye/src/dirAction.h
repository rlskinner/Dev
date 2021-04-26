#ifndef	_dirAction_
#define	_dirAction_

#include	"action.h"

class	dirAction : public action {
	weight	*primary;

	virtual	void	makeNbors();

public:
	dirAction( weight *_primary, weight *_wgt )
		: action( _wgt )
		{ primary = _primary; }

	virtual	void	init( int nDim, int dims[] );
	virtual void	doAction( cellArray *cells, int index[] );
};
	
#endif	/* _dirAction_ */
