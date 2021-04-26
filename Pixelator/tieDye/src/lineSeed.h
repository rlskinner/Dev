#ifndef	_lineSeed_
#define	_lineSeed_

#include	"seed.h"

class	lineSeed : public seed {
protected:
	double	x0, y0, x1, y1;
public:
		
	lineSeed( double x0, double y0, double x1, double y1, weight *wgt );

	virtual void	seedArray( cellArray *cells, int nDim, int dims[] );
};
	
#endif	/* _lineSeed_ */
