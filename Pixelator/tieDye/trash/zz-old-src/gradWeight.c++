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

    ilPixel pix;    
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


void
gradWeight::init( int nDim, int dims[] )
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



double  
gradWeight::getFunctionalWgt( int nDim, int abs[], int rel[] )
{
    int	pos[2], nrel[2];
    pos[0] = abs[0] - rel[0];
    pos[1] = abs[1] - rel[1];
    nrel[0] = -rel[0];
    nrel[1] = -rel[1];

    double	dx = delX->getWgt( nDim, pos, nrel );
    double	dy = delY->getWgt( nDim, pos, nrel );
    int len = rel[0]*rel[0] + rel[1]*rel[1];

    double	wgt = dx*rel[0] + dy*rel[1];
    if( len != 1 ) {
	wgt /= fsqrt( len );		// normalize by length
					// can do by table lookup, since
					// lengths are integer
    }
// printf( "del(%d,%d) = %g, %g  wgt = %g\n", pos[0], pos[1], dx, dy, wgt );
    return wgt > 0.0 ? wgt : 0.0;
}


