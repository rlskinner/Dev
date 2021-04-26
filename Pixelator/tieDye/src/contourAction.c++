//
//   eat an image away based on different rules, and different seed points
//

#include	"contourAction.h"
#include	<math.h>

//
//  precompute indexes of a dir, using 8-fold symetry
//
void
contourAction::init( int nDim, int dims[] )
{
	action::init( nDim, dims );
	primary->init( nDim, dims );

	if( nDim == 3 ) {
		printf( "3D contour not implemented\n" );
		return;
	}
}


void
contourAction::makeNbors()
{
    setNumNbors( 8*nDim );
    int numInds = 0;

	for( int x=-1; x<=1; x++ ) {
		for( int y=-1; y<=1; y++ ) {
			if( x == 0 && y == 0 ) 
				continue;

			nbors[numInds*nDim+0] = x;
			nbors[numInds*nDim+1] = y;
			numInds++;
		}
	}

    numNbors = numInds;
}

//
//  move index by relative values in inds, and add weight to each one
//
void
contourAction::doAction( cellArray *cells, int index[] )
{
    //
    //	Add the default weight to all empty neighbor cells:
    //  	the default action rule does the right thing, if the 
    //		selection state is empty
    //
    action::doAction( cells, index );

    // 
    //  now find the last neighbor to be filled
    //
    int	maxVal = -1;
    int	*maxInd = NULL;
    for( int i=0; i<numNbors; i++ ) {
	if( nborStates[i] == csFilled && nborValues[i] > maxVal ) {
#if	0
if( maxVal == -1 ) {
    printf( "contourAction::doAction( index = [" );
    for( int ii=0; ii<nDim; ii++ ) {
	printf( "%d", index[ii] );
	if( ii < nDim-1 )
	    putchar( ',' );
    }
    puts( "]" );
}
printf( "new max of %d at nbor = [", nborValues[i] );
    for( int ii=0; ii<nDim; ii++ ) {
	printf( "%d", nbors[i*nDim+ii] );
	if( ii < nDim-1 )
	    putchar( ',' );
    }
    puts( "]" );
#endif
	    maxVal = nborValues[i];
	    maxInd = &nbors[i*nDim];
	}
    }

    //
    //  and add the primary weight to the last filled
    //
    if( maxInd != NULL ) {
	//
	// add bigWgt to pixel OPPOSITE last one picked
	//	regardless of state
	//
	int	dir[3], rel[3];
	for( int j=0; j<nDim; j++ ) {
	    dir[j] = index[j] - maxInd[j];
	    rel[j] = -maxInd[j];
	}
	float	primWgt;
	primary->getWgts( nDim, 1, index, rel, &primWgt );
	cells->opPos( cfAdd, 1, index, rel, &primWgt );	// XXX use same function???
    }
}



