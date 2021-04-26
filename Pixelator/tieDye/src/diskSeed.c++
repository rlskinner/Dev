//
//   seed the cells with a disk of constant relative weight
//

#include	<math.h>

#include	"cellArray.h"
#include	"diskSeed.h"

diskSeed::diskSeed( int _cx, int _cy, int _rad, weight *wgt )
	: seed( wgt )
{
	cx = _cx;
	cy = _cy;
	radius = _rad;
	if( radius <= 0 )
	    radius = 1;
}


void
diskSeed::seedArray( cellArray *cells, int nDim, int dims[] )
{
    // overestimate number of indexes
    int	numInds = 0;
    int	*inds = new int[nDim*(2*radius+1)*(2*radius+1)];
    for( int y=0; y<=radius; y++ ) {
	for( int x=0; x<=radius; x++ ) {

	    //
	    //  see if we are inside disk
	    //
	    if( x*x + y*y > radius*radius )
		continue;

	    //
	    //  now use 4-fold symetry to set other values
	    //
	    inds[numInds*nDim+0] = cx+x;		// 1st quad
	    inds[numInds*nDim+1] = cx+y;
	    numInds++;

	    if( y != 0 ) {
		    inds[numInds*nDim+0] = cx+x;	// 4th quad
		    inds[numInds*nDim+1] = cx-y;
		    numInds++;
	    }
	    if( x != 0 ) {
		    inds[numInds*nDim+0] = cx-x;	// 2nd quad
		    inds[numInds*nDim+1] = cx+y;
		    numInds++;
	    }
	    if( x != 0 && y != 0 ) {
		    inds[numInds*nDim+0] = cx-x;	// 3rd quad
		    inds[numInds*nDim+1] = cx-y;
		    numInds++;
	    }
	}
    }

    int	origin[2];
    origin[0] = origin[1] = 0;
    float	*wgts = new float[numInds];
    wgt->getWgts( nDim, numInds, origin, inds, wgts );
    cells->opPos( cfAdd, numInds, origin, inds, wgts );

    delete wgts;
    delete inds;
}

