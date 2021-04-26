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
    //
    //  find number of points, and allocate a buffer for them
    //
    int	np;
    double	dx = x1 - x0;
    double	dy = y1 - y0;
    int		xMajor;
    double	delta;
    int		i, limit;
    if( dx == 0.0 && dy == 0.0 ) {
	np = 1;
    } else {
	if( fabs(dx) > fabs(dy) ) {
	    xMajor = 1;
	    delta = (y1-y0)/(x1-x0);
	    int	ix0 = int(rint(x0*dims[0]));
	    int	ix1 = int(rint(x1*dims[0]));
	    i = ( ix0 < ix1 ) ? ix0 : ix1;
	    limit = ( ix0 > ix1 ) ? ix0 : ix1;
	} else {
	    xMajor = 0;
	    delta = (x1-x0)/(y1-y0);
	    int	iy0 = int(rint(y0*dims[1]));
	    int	iy1 = int(rint(y1*dims[1]));
	    i = ( iy0 < iy1 ) ? iy0 : iy1;
	    limit = ( iy0 > iy1 ) ? iy0 : iy1;
	}
	np = limit-i+1;
    }

    int	*inds = new int[nDim*np];
    float	*wgts = new float[np];
    int		*ip;
    if( dx == 0.0 && dy == 0.0 ) {
	inds[0] = int(rint(x0*dims[0]));
	inds[1] = int(rint(y0*dims[1]));
    } else if( xMajor ) {
	for( ip = inds; i<=limit; i++, ip += nDim ) {
	    ip[0] = i;
	    ip[1] = int(rint( y0*dims[1] + (i - x0*dims[0])*delta ));
	}
    } else {
	for( ip = inds; i<=limit; i++, ip += nDim ) {
	    ip[0] = int(rint( x0*dims[0] + (i - y0*dims[1])*delta ));
	    ip[1] = i;
	}
    }

    int	origin[2];
    origin[0] = origin[1] = 0;
    wgt->getWgts( nDim, np, origin, inds, wgts );
    cells->opPos( cfAdd, np, origin, inds, wgts );

    delete inds;
    delete wgts;
}


