//
//   eat an image away based on different rules, and different seed points
//

#include	"cellArray.h"
#include	"imageSeed.h"
#include	"imageWeight.h"

#include	<string.h>
#include	<il/ilImage.h>
#include	<il/ilFileImg.h>


imageSeed::imageSeed( ilImage *_img, int tofit )
	: seed( new imageWeight( img ) /* XXXXXXXXXX */ )
{
	img = _img;
	toFit = tofit;
}

imageSeed::imageSeed( ilImage *_img, double _sx, double _sy )
	: seed( new imageWeight( _img ) /* XXXXXXXXXX */ )
{
	img = _img;
	toFit = 0;
	scale = 1;
	sx = _sx;
	sy = _sy;
}


void
imageSeed::seedArray( cellArray *cells, int nDim, int dims[] )
{
	//
	// open image filename, and determine scaling factors
	//
	long	nx = img->getXsize();
	long	ny = img->getYsize();
	if( toFit ) {
		sx = double(dims[0])/double(nx);
		sy = double(dims[1])/double(ny);
		scale = 1;
	}
	if( scale ) {
		printf( "scale image by (%g,%g)\n", sx, sy );
	}

	printf( "min = %g, max = %g\n", img->getMinValue(), img->getMaxValue() );

	if( nDim == 2 ) {
	    int	chan[1];
	    chan[0] = 0;
	    ilConfig	config( iflFloat, iflInterleaved, 1, chan );
	    float	pix[16*16];
	    int		rel[2];
	    rel[0] = rel[1] = 0;
	    for( int j=0; j<ny; j += 16 ) {
		int ty = 16;
		if( j+ty > ny ) ty = ny - j;

		for( int i=0; i<nx; i += 16 ) {
		    int tx = 16;
		    if( i+tx > nx ) tx = nx - i;

		    img->getTile( i, j, tx, ty, pix, &config );

	    	    int	ind[2];
		    for( int jj=0; jj<ty; jj++ ) {
			ind[1] = j+jj;
			for( int ii=0; ii<tx; ii++ ) {
			    ind[0] = i+ii;
			    cells->opPos( cfAdd, 1, ind, rel, &pix[jj*ty+ii] );
			}
		    }
		}
	    }
	}
}


