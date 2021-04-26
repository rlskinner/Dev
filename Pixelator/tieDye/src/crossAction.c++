//
//   eat an image away based on different rules, and different seed points
//

#include	"crossAction.h"
#include	<math.h>
#include	<assert.h>

//
//  precompute indexes of a cross, using 4-fold symetry
//
void
crossAction::init( int nDim, int dims[] )
{
	action::init( nDim, dims );

	if( nDim == 3 ) {
		printf( "3D cross (sphere) not implemented\n" );
		return;
	}
}


void
crossAction::makeNbors()
{
	setNumNbors( 4*size );
	int numInds = 0;
	for( int x=1; x<=size; x++ ) {

		// compute linear ramp of weight from max at center 
		//	to 0 outside radius
		// RFE: this could be any exponent of distance
		double	w = 1.0 - x/size;
		if( w < 0.0 ) continue;
		
		//
		//  now use 4-fold symetry to set other values
		//

		nbors[numInds*nDim+0] = +x;		// right
		nbors[numInds*nDim+1] = +0;
		relNborWgts[numInds] = w;
		numInds++;

		nbors[numInds*nDim+0] = -x;		// left
		nbors[numInds*nDim+1] = +0;
		relNborWgts[numInds] = w;
		numInds++;

		nbors[numInds*nDim+0] = +0;		// down
		nbors[numInds*nDim+1] = +x;
		relNborWgts[numInds] = w;
		numInds++;

		nbors[numInds*nDim+0] = +0;		// down
		nbors[numInds*nDim+1] = -x;
		relNborWgts[numInds] = w;
		numInds++;
	}
	assert( numInds <= numNbors );
	numNbors = numInds;
}



