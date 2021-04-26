#ifndef	_enCrossAction_
#define	_enCrossAction_

#include	"enAction.h"

class	enCrossAction : public enAction {
protected:
	int	_size;

	virtual	void	makeNbors();

public:
	enCrossAction( enWeight *wgt, int sz )
		: enAction( wgt )
		{ size = sz;  }

	virtual	void	init( int nDim, int dims[] );
};
	
#endif	/* _enCrossAction_ */
