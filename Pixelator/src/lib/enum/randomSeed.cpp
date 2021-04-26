//
//   Enumerate the pixels in an image away based on different rules, and
//   different seed points
//

#include	<math.h>

#include	"CellArray.h"
#include	"randomSeed.h"

void
randomSeed::seedArray(CellArray *cells, // CellArray to seed
		      int nDim, // # dimensions
		      int dims[] // actual dimensions
		     )
{
    int	origin[2];
    origin[0] = origin[1] = 0;

    double	*wgts = new double[numSeeds];
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

// vim:ts=8:
