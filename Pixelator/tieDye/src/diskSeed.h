#ifndef	_diskSeed_
#define	_diskSeed_

#include	"seed.h"

class	diskSeed : public seed {
protected:
	int	cx, cy, radius;
public:
		
	diskSeed( int cx, int cy, int rad, weight *wgt );

	virtual void	seedArray( cellArray *cells, int nDim, int dims[] );
};
	
#endif	/* _diskSeed_ */
