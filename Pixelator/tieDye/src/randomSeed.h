#ifndef	_randomSeed_
#define	_randomSeed_

#include	"seed.h"

class	randomSeed : public seed {
	int	numSeeds;

public:
	randomSeed( weight *wgt, int seeds ) 
		: seed( wgt ) 
		{ numSeeds = seeds; }

	virtual void	seedArray( cellArray *cells, int nDim, int dims[] );
};
	
#endif	/* _randomSeed_ */
