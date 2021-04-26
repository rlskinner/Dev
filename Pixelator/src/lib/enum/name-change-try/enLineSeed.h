#ifndef	_enLineSeed_
#define	_enLineSeed_

#include	"seed.h"

class	lineSeed : public seed {
protected:
	double	x0, y0, x1, y1;
public:
		
	lineSeed( double x0, double y0, double x1, double y1, enWeight *wgt );

	virtual void	seedArray( enCellArray *cells, int nDim, int dims[] );
};
	
#endif	/* _enLineSeed_ */
