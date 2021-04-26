//
//   eat an image away based on different rules, and different seed points
//

#include	<math.h>

#include	"cellArray.h"
#include	"lineSeed.h"

lineSeed::lineSeed( double _x0, double _y0, double _x1, double _y1, weight *wgt )
	: seed( wgt )
{
	x0 = ( _x0 > 1.0 ) ? 1.0 : (( _x0 < 0.0 ) ? 0.0 : _x0);
	y0 = ( _y0 > 1.0 ) ? 1.0 : (( _y0 < 0.0 ) ? 0.0 : _y0);
	x1 = ( _x1 > 1.0 ) ? 1.0 : (( _x1 < 0.0 ) ? 0.0 : _x1);
	y1 = ( _y1 > 1.0 ) ? 1.0 : (( _y1 < 0.0 ) ? 0.0 : _y1);
}


void
lineSeed::seedArray( cellArray *cells, int nDim, int dims[] )
{
	int	ind[2];
	double	dx = x1 - x0;
	double	dy = y1 - y0;

	if( dx == 0.0 && dy == 0.0 ) {
		ind[0] = int(rint(x0*dims[0]));
		ind[1] = int(rint(y0*dims[1]));
		cells->add( ind, wgt->getWgt( nDim, ind, ind ) );
	} else if( fabs(dx) > fabs(dy) ) {
		int	ix0 = int(rint(x0*dims[0]));
		int	ix1 = int(rint(x1*dims[0]));
		double	delta = (y1-y0)/(x1-x0);
		int	i = ( ix0 < ix1 ) ? ix0 : ix1;
		int	limit = ( ix0 > ix1 ) ? ix0 : ix1;
		for( ; i<=limit; i++ ) {
			ind[0] = i;
			ind[1] = int(rint( y0*dims[1] + (i - x0*dims[0])*delta ));
			cells->add( ind, wgt->getWgt( nDim, ind, ind ) );
		}
	} else {
		int	iy0 = int(rint(y0*dims[1]));
		int	iy1 = int(rint(y1*dims[1]));
		double	delta = (x1-x0)/(y1-y0);
		int	i = ( iy0 < iy1 ) ? iy0 : iy1;
		int	limit = ( iy0 > iy1 ) ? iy0 : iy1;
		for( ; i<=limit; i++ ) {
			ind[0] = int(rint( x0*dims[0] + (i - y0*dims[1])*delta ));
			ind[1] = i;
			cells->add( ind, wgt->getWgt( nDim, ind, ind ) );
		}
	}
}


