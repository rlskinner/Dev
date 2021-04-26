#ifndef	_ContourAction_
#define	_ContourAction_

#include	"enAction.h"

class	enContourAction : public enAction {
protected:
	enWeight	*_primary;

	virtual	void	makeNbors();

public:
	enContourAction( enWeight *_wgt )
		: enAction( _wgt )
		{ }

	virtual	void	init( int nDim, int dims[] );
	virtual void	doAction( enCellArray *cells, int index[] );
};
	
#endif	/* _enContourAction_ */
