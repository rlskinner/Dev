#ifndef	_edgeSeed_
#define	_edgeSeed_

#include	"seed.h"

class	edgeSeed : public seed {
public:
	edgeSeed( weight *wgt ) : seed( wgt ) {}

	virtual void	seedArray( cellArray *cells, int nDim, int dims[] );
};
	
#endif	/* _edgeSeed_ */
