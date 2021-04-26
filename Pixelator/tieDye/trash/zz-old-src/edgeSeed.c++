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
	int	ind[2];

	if( nDim == 2 ) {
		for( i=0; i<dims[1]; i++ ) {
			ind[1] = i;
	
			ind[0] = 0;
			cells->add( ind, wgt->getWgt( nDim, ind, ind ) );
	
			ind[0] = dims[0]-1;
			cells->add( ind, wgt->getWgt( nDim, ind, ind ) );
		}
	
		for( i=1; i<dims[0]-1; i++ ) {
			ind[0] = i;
	
			ind[1] = 0;
			cells->add( ind, wgt->getWgt( nDim, ind, ind ) );
	
			ind[1] = dims[1]-1;
			cells->add( ind, wgt->getWgt( nDim, ind, ind ) );
		}
	}
}


