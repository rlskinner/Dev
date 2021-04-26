//
//   eat an image away based on different rules, and different seed points
//

#include	"cellArray.h"
#include	"edgeSeed.h"

//
//  XXX doesn't use correct relative weight coordinates
//
void
edgeSeed::seedArray( cellArray *cells, int nDim, int dims[] )
{
	int	i;
	int	origin[2];
	int	*rel;
	float	*wgts;

	int	len = ( dims[0] > dims[1] ) ? dims[0] : dims[1];
	len *= 2;
	rel = new int[nDim*len];
	wgts = new float[len];
	origin[0] = origin[1] = 0;

	int	*rp;
	if( nDim == 2 ) {
		rp = rel;
		for( i=0; i<dims[1]; i++ ) {
		    rp[0] = 0;
		    rp[1] = i;
		    rp += nDim;
		    rp[0] = dims[0]-1;
		    rp[1] = i;
		    rp += nDim;
		}
		wgt->getWgts( nDim, 2*dims[1], origin, rel, wgts );
		cells->opPos( cfAdd, 2*dims[1], origin, rel, wgts );

		rp = rel;
		for( i=1; i<dims[0]-1; i++ ) {
		    rp[0] = i;
		    rp[1] = 0;
		    rp += nDim;
		    rp[0] = i;
		    rp[1] = dims[1]-1;
		    rp += nDim;
		}
		wgt->getWgts( nDim, 2*(dims[0]-2), origin, rel, wgts );
		cells->opPos( cfAdd, 2*(dims[0]-2), origin, rel, wgts );
	}

	delete rel;
	delete wgts;
}


