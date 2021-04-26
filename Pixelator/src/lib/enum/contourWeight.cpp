#include	"contourWeight.h"
#include	<math.h>
#include	<unistd.h>
#include	<stdlib.h>
#include	<bstring.h>


contourWeight::contourWeight( weight *_contour, weight *_scale, double _dropoff )
	: weight()
{
    contour = _contour;
    scale = _scale;
    dropoff = _dropoff;
}


contourWeight::~contourWeight()
{
    delete contour;
    delete scale;
}


void
contourWeight::init(int nDim, // # dimensions
		    int dims[] // actual dimensions
		   )
{
    contour->init( nDim, dims );
}




//
// Get an array of weights for the given array of indexes
// 	contourWeight uses the function: exp(-abs(selected-offset))
//
void contourWeight::getWgts(int nDim, // # dimensions
		       int n, // number of indexes
		       int absIndexes[], // list of absolute indexes [n]
		       int relIndexes[], // list of relative indexes [n]
		       double wgts[] // out: weights [n]
		      )
{
    float	thisVal;
    int	thisRel[2];
    thisRel[0] = thisRel[1] = 0;

    contour->getWgts( nDim, 1, selected, thisRel, &thisVal );	// get my value

    float	nborWgts[256];		// get neighbor's values
    contour->getWgts( nDim, n, selected, off, nborWgts );

    float	nborScales[256];		// get scale factors
    contour->getWgts( nDim, n, selected, off, nborScales );

    for( int i=0; i<n; i++ ) {
	wgts[i] = nborScales[i]*fexp( -dropoff*fabsf( thisVal - nborWgts[i] ) );
    }
}




// vim:ts=8:
