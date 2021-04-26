#ifndef	_seed_
#define	_seed_

#include	<stdio.h>

#include	"weight.h"

class	cellArray;

class	seed {
protected:
	weight	*wgt;

public:
	seed	*next;
	seed( weight *_wgt )		{ wgt = _wgt; next = NULL; }

	virtual	void	init( int nDim, int dims[] );

	virtual void	seedArray( cellArray *cells, int nDim, int dims[] ) = 0;
};
	
#endif	/* _seed_ */
