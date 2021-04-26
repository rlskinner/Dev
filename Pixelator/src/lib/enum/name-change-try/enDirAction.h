#ifndef	_enDirAction_
#define	_enDirAction_

#include	"enAction.h"

class	enDirAction : public enAction {
protected:
	enWeight	*_primary;

	virtual	void	makeNbors();

public:
	enDirAction( enWeight *_primary, enWeight *_wgt )
		: enAction( _wgt )
		{ primary = _primary; }

	virtual	void	init( int nDim, int dims[] );
	virtual void	doAction( enCellArray *cells, int index[] );
};
	
#endif	/* _enDirAction_ */
