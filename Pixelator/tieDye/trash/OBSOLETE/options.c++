#include	<stdio.h>
#include	<stdlib.h>
#include	<libc.h>
#include	<unistd.h>
#include	<string.h>
#include	<fcntl.h>
#include	<limits.h>

#include	"options.h"
#include	"parseIF.h"

//
//  all of the seeds and actions we know about
//
#include	"edgeSeed.h"
#include	"lineSeed.h"
#include	"randomSeed.h"
#include	"imageSeed.h"

#include	"nborAction.h"
#include	"edgeAction.h"
#include	"cornerAction.h"
#include	"ringAction.h"
#include	"coneAction.h"
#include	"crossAction.h"
#include	"dirAction.h"

static	options	*ops;

extern	"C"	void yyparse();

options*
parseOptions( int argc, char *argv[] )
{
	// find the file if possible
	if( argc > 1 ) {
		int	f = open( argv[1], 0 );
		if( f >= 0 ) {
			ops = new options;

			int	si = dup( 0 );		// save stdin
			dup2( f, 0 );			// make file stdin
			yyparse();
			close( 0 );
			close( f );
			dup2( si, 0 );			// restore old stdin
			return ops;
		} else {
			fprintf( stderr, "error opening options file %s\n",
				argv[1] );
		}
	}

	ops = new options;
	yyparse();
	return ops;
}



options::options()
{
	dims = NULL;
	seeds = NULL;
	actions = NULL;

	setPosition = 0;
	loadCmap = 0;
	cmapFilename = NULL;
	writeFile = 0;
	writeFilename = NULL;
}


void
_setSize( int sx, int sy )
{
	delete ops->dims;
	ops->dims = new int[2];
	ops->dims[0] = sx;
	ops->dims[1] = sy;
}


void
_setSizeAt( int sx, int sy, int px, int py )
{
	delete ops->dims;
	ops->dims = new int[2];
	ops->dims[0] = sx;
	ops->dims[1] = sy;

	ops->setPosition = 1;
	ops->wx = px;
	ops->wy = py;
}



void
_loadCmap( char *file )
{
	ops->loadCmap = 1;
	ops->cmapFilename = strdup( file );
}


void
_edgeSeed( weight *wgt )
{
	edgeSeed	*seed = new edgeSeed( wgt );
	ops->addSeed( seed );
}

void
_lineSeed( double x0, double y0, double x1, double y1, weight *wgt )
{
	lineSeed	*seed = new lineSeed( x0, y0, x1, y1, wgt );
	ops->addSeed( seed );
}


void
_randomIntSeed( int num, weight *wgt )
{
	randomSeed	*rs = new randomSeed( wgt, num );
	ops->addSeed( rs );
}

void
_randomPerCentSeed( double percent, weight *wgt )
{
}


void
_imageSeed( ilImage *img, int fit, double sx, double sy )
{
	imageSeed *is;
	if( fit ) {
		is = new imageSeed( img, 1 );
	} else {
		is = new imageSeed( img, sx, sy );
	}
	ops->addSeed( is );
}

void
_nborAction( int connectedness, weight *wgt )
{
	nborAction	*act = new nborAction( wgt, connectedness );
	ops->addAction( act );
}

void
_edgeAction( weight *wgt )
{
	edgeAction	*act = new edgeAction( wgt );
	ops->addAction( act );
}

void
_dirAction( weight *primary, weight *wgt )
{
	dirAction	*act = new dirAction( primary, wgt );
	ops->addAction( act );
}

void
_cornerAction( weight *wgt )
{
	cornerAction	*act = new cornerAction( wgt );
	ops->addAction( act );
}

void
_ringAction( int radius, weight *wgt )
{
	ringAction	*act = new ringAction( wgt, radius );
	ops->addAction( act );
}

void
_scatterRingAction( int radius, weight *wgt )
{
}

void
_coneAction( int radius, weight *wgt )
{
	coneAction	*act = new coneAction( wgt, radius );
	ops->addAction( act );
}


void
_crossAction( int radius, weight *wgt )
{
	crossAction	*act = new crossAction( wgt, radius );
	ops->addAction( act );
}


//////////////////////////////////////////////////////////////////////
//  image creation, construction, etc
//
ilImage*
_openImageFile( char *filename )
{
	ilImage *img = ilOpenImgFile(filename,"r");	// no conversions here
	ilPixel	min, max;
	img->getMinPixel( min );
	img->getMaxPixel( max );
	int	i;
	switch( min.type() ) {
#define	CASE(iltype,minval,maxval)					\
		case iltype:						\
			for( i=0; i<min.nc(); i++ ) {			\
				img->setMinValue( minval, i );		\
				img->setMaxValue( maxval, i );		\
			}						\
			break						
		CASE(ilBit,0,1);
		CASE(ilUChar,0,UCHAR_MAX);
		CASE(ilChar,SCHAR_MIN,SCHAR_MAX);
		CASE(ilUShort,0,USHRT_MAX);
		CASE(ilShort,SHRT_MIN,SHRT_MAX);
		CASE(ilULong,0,ULONG_MAX);
		CASE(ilLong,LONG_MIN,LONG_MAX);
		CASE(ilFloat,0.0,1.0);
		CASE(ilDouble,0.0,1.0);
#undef	CASE
	}
	printf( "open: min = %g, max = %g\n", img->getMinValue(), img->getMaxValue() );
	return img;
}

ilImage*
_scaleImage( double s, ilImage *inImg )
{
	ilPixel	pix( ilDouble, 1, &s );
	ilImage *outImg = new ilMultiplyImg( inImg, new ilConstImg( pix ) );
	printf( "scale: min = %g, max = %g\n", outImg->getMinValue(), outImg->getMaxValue() );
	return outImg;
}

ilImage*
_zoomImageToFit( ilImage *inImg )
{
	printf( "where can I be assured of getting the size?\n" );
	exit( -1 );
	ilImage *outImg = NULL;
	printf( "zoom: min = %g, max = %g\n", outImg->getMinValue(), outImg->getMaxValue() );
	return outImg;
}

ilImage*
_zoomImage( double zx, double zy, ilImage *inImg )
{
	ilImage *outImg = new ilRotZoomImg( inImg, 0.0, zx, zy, ilNoFlip, ilBiLinear ); 
	printf( "zoom: min = %g, max = %g\n", outImg->getMinValue(), outImg->getMaxValue() );
	return outImg;
}



//////////////////////////////////////////////////////////////////////
//  image operators
//

ilImage*
_invertImage( ilImage *inImg )
{
    ilImage *outImg = new ilInvertImg( inImg );
    printf( "invert: min = %g, max = %g\n", outImg->getMinValue(), outImg->getMaxValue() );
    return outImg;
}

ilImage*
_negImage( ilImage *inImg )
{
    ilImage *outImg = new ilNegImg( inImg );
    printf( "neg: min = %g, max = %g\n", outImg->getMinValue(), outImg->getMaxValue() );
    return outImg;
}

ilImage*
_sharpenImage( ilImage *inImg, double sh, double rad )
{
    ilImage *outImg;
    if( sh == DEFAULT_VALUE ) {
	outImg = new ilSharpenImg( inImg );
	printf( "ilSharpenImg( * )\n" );
    } else if( rad == DEFAULT_VALUE ) {
        outImg = new ilSharpenImg( inImg, sh );
	printf( "ilSharpenImg( *, %g )\n", sh );
    } else {
	outImg = new ilSharpenImg( inImg, sh, rad );
	printf( "ilSharpenImg( *, %g, %g )\n", sh, rad );
    }
    return outImg;
}

ilImage*
_threshImage( ilImage *inImg, double val )
{
    ilImage *outImg = new ilThreshImg( inImg, val );
    printf( "thresh: min = %g, max = %g\n", outImg->getMinValue(), outImg->getMaxValue() );
    return outImg;
}

//////////////////////////////////////////////////////////////////////
//  sophisticated weights
//
weight*
_constWeight( double w )
{
	return new constWeight( w );
}

weight*
_imageWeight( ilImage *img )
{
	return new imageWeight( img );
}

weight*
_lastdirWeight( weight *dirWt, weight *offDirWt )
{
	abort();
	return NULL;
}





