//
//   eat an image away based on different rules, and different seed points
//

#include	<math.h>

#include	"cellArray.h"
#include	"randomSeed.h"

void
randomSeed::seedArray( cellArray *cells, int nDim, int dims[] )
{
    int	origin[2];
    origin[0] = origin[1] = 0;

    float	*wgts = new float[numSeeds];
    int	*rel = new int[nDim*numSeeds];
    int *rp = rel;
    for( int i=0; i<numSeeds; i++, rp += nDim ) {
	rp[0] = random() % dims[0];
	rp[1] = random() % dims[1];
    }
    wgt->getWgts( nDim, numSeeds, origin, rel, wgts );
    cells->opPos( cfAdd, numSeeds, origin, rel, wgts );

    delete wgts;
    delete rel;
}
