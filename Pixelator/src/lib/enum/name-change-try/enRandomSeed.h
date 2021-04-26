#ifndef	_enRandomSeed_
#define	_enRandomSeed_

#include	"seed.h"

class	randomSeed : public seed {
	int	numSeeds;

public:
	randomSeed( enWeight *wgt, int seeds ) 
		: seed( wgt ) 
		{ numSeeds = seeds; }

	virtual void	seedArray( enCellArray *cells, int nDim, int dims[] );
};
	
#endif	/* _enRandomSeed_ */
