#ifndef	_edgeSeed_
#define	_edgeSeed_

#include	"seed.h"

class	EdgeSeed : public Seed 
    {
    public:
	EdgeSeed(Weight *wgt) 
	    : Seed( wgt ) 
	    {}

	virtual std::string name();

	virtual void	seedArray(CellArray *cells, Dimensions const& dims);
    };
	
#endif	/* _EdgeSeed_ */

// vim:ts=8:
