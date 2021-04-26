//
//   eat an image away based on different rules, and different seed points
//

#include	"coneAction.h"
#include	<math.h>
#include	<assert.h>

//
//  precompute indexes of a cone, using 8-fold symetry
//
void
coneAction::init( int nDim, int dims[] )
{
	action::init( nDim, dims );

	if( nDim == 3 ) {
		printf( "3D cone (sphere) not implemented\n" );
		return;
	}
}


void
coneAction::makeNbors()
{
	// overestimate number of indexes
	setNumNbors( (2*radius+1)*(2*radius+1) );
	addState = csWaiting;
	int	numInds = 0;
	for( int y=0; y<=radius; y++ ) {
	    for( int x=0; x<=radius; x++ ) {

		// compute distance from center
		double 	dist = sqrt(double(x*x + y*y));

		// compute linear ramp of weight from max at center 
		//	to 0 outside radius
		// RFE: this could be any exponent of distance
		double	w = 1.0 - dist/radius;
		if( w < 0.0 ) continue;
		
		//
		//  now use 4-fold symetry to set other values
		//

		nbors[numInds*nDim+0] = +x;		// 1st quad
		nbors[numInds*nDim+1] = +y;
		nborWgts[numInds] = w;
		numInds++;

		if( y != 0 ) {
			nbors[numInds*nDim+0] = +x;	// 4th quad
			nbors[numInds*nDim+1] = -y;
			nborWgts[numInds] = w;
			numInds++;
		}
		if( x != 0 ) {
			nbors[numInds*nDim+0] = -x;	// 2nd quad
			nbors[numInds*nDim+1] = +y;
			nborWgts[numInds] = w;
			numInds++;
		}
		if( x != 0 && y != 0 ) {
			nbors[numInds*nDim+0] = -x;	// 3rd quad
			nbors[numInds*nDim+1] = -y;
			nborWgts[numInds] = w;
			numInds++;
		}
	    }
	}
	assert( numInds <= numNbors );
	numNbors = numInds;
}


