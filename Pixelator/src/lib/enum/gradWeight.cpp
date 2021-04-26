#include	"gradWeight.h"
#include	<math.h>
#include	<unistd.h>
#include	<stdlib.h>
#include	<bstring.h>


void
print( char *name, ilImage *img )
{
    printf( "\n%s:\n", name );
    printf( "    " );
    for( int i=0; i<16; i++ ) {
	printf( "%4d", i );
    }
    printf( "\n" );

    iflPixel pix;    
    for( int j=15; j>=0; j-- ) {
	printf( "%3d ", j );
	for( int i=0; i<16; i++ ) {
	    img->getPixel( i, j, pix );
	    printf( "%4d", int(pix[0]) );
	}
	printf( "\n" );
    }
    printf( "\n" );
}

gradWeight::gradWeight( weight *delx, weight *dely )
	: weight()
{
    delX = delx;
    delY = dely;

    // print( "del X", delx );
    // print( "del Y", dely );

    sqrtTblLen = 4;
    sqrtTbl = new float[4];
    for( int i=0; i<4; i++ ) {
	sqrtTbl[i] = fsqrt( float(i) );
    }
}


gradWeight::~gradWeight()
{
    delete delX;
    delete delY;

    delete sqrtTbl;
}


// 
// Initialize the gradWeight from the cell array dimensions
//
void gradWeight::init(int nDim, // # dimensions
		      int dims[] // actual dimensions
		     )
{
    delX->init( nDim, dims );
    delY->init( nDim, dims );
}


float
gradWeight::sqrt( int d )
{
    if( d < 0 )
	return -1;

    if( d >= sqrtTblLen ) {
	int	newLen = 2*(d+1);
	float	*tbl = new float[newLen];
	bcopy( sqrtTbl, tbl, sqrtTblLen*sizeof(float) );

	for( int i=sqrtTblLen; i<newLen; i++ ) {
	    tbl[i] = fsqrt( float(i) );
	}

	delete sqrtTbl;
	sqrtTbl = tbl;
	sqrtTblLen = newLen;
    }

    return sqrtTbl[d];
}



//
// Get an array of weights for the given array of indexes
// 	gradWeight computes the one gradient at the abs position, then
// 	take the dot product with the actual positions
//
void gradWeight::getWgts(int nDim, // # dimensions
			 int n, // number of indexes
			 int absIndexes[], // list of absolute indexes [n]
			 int relIndexes[], // list of relative indexes [n]
			 double wgts[] // out: weights [n]
			)
{
    float	dx, dy;
    int	nrel[2];
    nrel[0] = nrel[1] = 0;

    delX->getWgts( nDim, 1, selected, nrel, &dx );
    delY->getWgts( nDim, 1, selected, nrel, &dy );

    for( int i=0; i<n; i++ ) {
	int	len = off[nDim*i]*off[nDim*i] + off[nDim*i+1]*off[nDim*i+1];
	wgts[i] = dx*off[nDim*i] + dy*off[nDim*i+1];
	if( len != 1 && len != 0 ) {
	    wgts[i] /= fsqrt( len );		// normalize by length
	}
    }
}




// vim:ts=8:
