//
//   eat an image away based on different rules, and different seed points
//

#include	<math.h>

#include	"cellArray.h"
#include	"randomSeed.h"

void
randomSeed::seedArray( cellArray *cells, int nDim, int dims[] )
{
	int	i;
	int	ind[2];

	for( i=0; i<numSeeds; i++ ) {
		ind[0] = random() % dims[0];
		ind[1] = random() % dims[1];
		cells->add( ind, wgt->getWgt( nDim, ind, ind ) );
	}
}
