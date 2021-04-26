#ifndef	_enEdgeSeed_
#define	_enEdgeSeed_

#include	"seed.h"

class	enEdgeSeed : public seed {
public:
	enEdgeSeed( enWeight *wgt ) : seed( wgt ) {}

	virtual void	seedArray( enCellArray *cells, int nDim, int dims[] );
};
	
#endif	/* _enEdgeSeed_ */
