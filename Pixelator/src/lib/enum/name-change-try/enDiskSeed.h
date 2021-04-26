#ifndef	_enDiskSeed_
#define	_enDiskSeed_

#include	"seed.h"

class	enDiskSeed : public seed {
protected:
	int	cx, cy, radius;
public:
		
	enDiskSeed( int cx, int cy, int rad, enWeight *wgt );

	virtual void	seedArray( enCellArray *cells, int nDim, int dims[] );
};
	
#endif	/* _enDiskSeed_ */
