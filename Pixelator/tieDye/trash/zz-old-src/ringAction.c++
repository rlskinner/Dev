//
//   eat an image away based on different rules, and different seed points
//

#include	"ringAction.h"
#include	<math.h>
#include	<assert.h>

ringAction::ringAction( weight *_wgt, int rad )
	: action( _wgt )
{
	radius = rad;
}

void
ringAction::init( int nDim, int dims[] )
{
	action::init( nDim, dims );

	if( nDim == 3 ) {
		printf( "3D ring (sphere) not implemented\n" );
		return;
	}
}



//
//  precompute indexes of a ring, using 8-fold symetry
//
void
ringAction::makeNbors()
{
	addState = csWaiting;
	setNumNbors( 8*radius );	// overestimate number of indexes
	setConstWgts();
	int	numInds = 0;
	for( int y=0; y<radius; y++ ) {
		int	x = int(rint(sqrt(double(radius*radius-y*y))));
		if( y <= x ) {		// only do first octant, then fold
			nbors[numInds*nDim+0] = +x;
			nbors[numInds*nDim+1] = +y;
			numInds++;
			if( y != 0 ) {
				nbors[numInds*nDim+0] = +x;	// 8th octant
				nbors[numInds*nDim+1] = -y;
				numInds++;
			}
			if( x != 0 ) {
				nbors[numInds*nDim+0] = -x;	// 4rd octant
				nbors[numInds*nDim+1] = +y;
				numInds++;
			}
			if( x != 0 && y != 0 ) {
				nbors[numInds*nDim+0] = -x;	// 5th octant
				nbors[numInds*nDim+1] = -y;
				numInds++;
			}

			if( y == x ) continue;

			nbors[numInds*nDim+0] = +y;	// 2nd octant
			nbors[numInds*nDim+1] = +x;
			numInds++;
			if( x != 0 ) {
				nbors[numInds*nDim+0] = +y;	// 3th octant
				nbors[numInds*nDim+1] = -x;
				numInds++;
			}
			if( y != 0 ) {
				nbors[numInds*nDim+0] = -y;	// 6rd octant
				nbors[numInds*nDim+1] = +x;
				numInds++;
			}
			if( x != 0 && y != 0 ) {
				nbors[numInds*nDim+0] = -y;	// 7th octant
				nbors[numInds*nDim+1] = -x;
				numInds++;
			}
		}
	}

	assert( numInds <= numNbors );
	numNbors = numInds;		// set real number of indexes length
}



