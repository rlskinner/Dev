#ifndef	_enSeed_
#define	_enSeed_

#include	<stdio.h>

#include	"enWeight.h"

class	enCellArray;

class	seed {
protected:
	enWeight	*wgt;

public:
	seed	*next;
	seed( enWeight *_wgt )		{ wgt = _wgt; next = NULL; }

	virtual	void	init( int nDim, int dims[] );

	virtual void	seedArray( enCellArray *cells, int nDim, int dims[] ) = 0;
};
	
#endif	/* _enSeed_ */
