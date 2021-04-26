#include	<stdio.h>
#include	<stdlib.h>
#include	<libc.h>
#include	<unistd.h>
#include	<string.h>
#include	<fcntl.h>
#include	<limits.h>

#include	"eat.h"
#include	"parse.h"
#include	"y.tab.h"

//
//  all of the seeds and actions we know about
//
#include	"diskSeed.h"
#include	"edgeSeed.h"
#include	"lineSeed.h"
#include	"randomSeed.h"
#include	"imageSeed.h"

#include	"nborAction.h"
#include	"cornerAction.h"
#include	"ringAction.h"
#include	"coneAction.h"
#include	"crossAction.h"
#include	"dirAction.h"



void
_setSize( int sx, int sy )
{
    eatApp->setSize( sx, sy );
}


void
_setSizeAt( int sx, int sy, int px, int py )
{
    eatApp->setSize( sx, sy, px, py );
}


void
_loadColormap( char *file )
{
	eatApp->loadColormap( file );
}


void
_writeImage( char *file, int type )
{
    eatApp->setWriteImage( file, (char *)&type );
}

void
_exitWhenDone()
{
    eatApp->setExit();
}


void
_edgeSeed( weight *wgt )
{
	edgeSeed	*seed = new edgeSeed( wgt );
	eatApp->addSeed( seed );
}

void
_diskSeed( int cx, int cy, int radius, weight *wgt )
{
	diskSeed	*seed = new diskSeed( cx, cy, radius, wgt );
	eatApp->addSeed( seed );
}


void
_lineSeed( double x0, double y0, double x1, double y1, weight *wgt )
{
	lineSeed	*seed = new lineSeed( x0, y0, x1, y1, wgt );
	eatApp->addSeed( seed );
}


void
_randomIntSeed( int num, weight *wgt )
{
	randomSeed	*rs = new randomSeed( wgt, num );
	eatApp->addSeed( rs );
}

void
_randomPerCentSeed( double /* percent */, weight* /* wgt */ )
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
	eatApp->addSeed( is );
}

////////////////////////////////////////////////////////
//
//  Action options
//
////////////////////////////////////////////////////////
actionWeightSelect	actionWeight;
int			selectState;
cellFunction		actionFunction;

int			actionWeightSet,	// flags indicate whether set
			selectStateSet,
			actionFunctionSet;
void
_initActionOptions()
{
    actionWeight = awPositive;	
    selectState = csWaiting;
    actionFunction = cfAdd;

    actionWeightSet = selectStateSet = actionFunctionSet = FALSE;
}

void
_setStateOption( int val )
{
    selectStateSet = TRUE;
    switch( val ) {
	case ANY:	selectState = csEmpty | csWaiting;	break;
	case EMPTY:	selectState = csEmpty;			break;
	case WAITING:	selectState = csWaiting;		break;
    }
}

void
_setFunctionOption( int val )
{
    actionFunctionSet = TRUE;
    switch( val ) {
	case SET:	actionFunction = cfSet;		break;
	case ADD:	actionFunction = cfAdd;		break;
	case MULTIPLY:	actionFunction = cfMultiply;	break;
    }
}

void
_setWeightOption( int val )
{
    actionWeightSet = TRUE;
    switch( val ) {
	case ALL:	actionWeight = awAll;		break;
	case MAX:	actionWeight = awMax;		break;
	case MIN:	actionWeight = awMin;		break;
	case POSITIVE:	actionWeight = awPositive;	break;
	case NEGATIVE:	actionWeight = awNegative;	break;
    }
}

static void
_applyActionOptions( action *act )
{
    if( selectStateSet ) act->setStateSelection( selectState );
    if( actionFunctionSet ) act->setWeightFunction( actionFunction );
    if( actionWeightSet ) act->setWeightSelection( actionWeight );
}


void
_nborAction( int connectedness, weight *wgt )
{
	nborAction	*act = new nborAction( wgt, connectedness );
	eatApp->addAction( act );
	_applyActionOptions( act );
}

void
_ringAction( int radius, weight *wgt )
{
	ringAction	*act = new ringAction( wgt, radius );
	eatApp->addAction( act );
	_applyActionOptions( act );
}

void
_edgeAction( weight *wgt )
{
	nborAction	*act = new nborAction( wgt, 4 );
	eatApp->addAction( act );
	_setStateOption( ANY );		// edgeAction == nborAction, this way
	_applyActionOptions( act );
}

void
_dirAction( weight *primary, weight *wgt )
{
	dirAction	*act = new dirAction( primary, wgt );
	eatApp->addAction( act );
	_setStateOption( EMPTY );	// this is how it was originally coded
	_applyActionOptions( act );
}

void
_cornerAction( weight *wgt )
{
	cornerAction	*act = new cornerAction( wgt );
	eatApp->addAction( act );
	_applyActionOptions( act );
}


void
_scatterRingAction( int /* radius */, weight* /* wgt */ )
{
}

void
_coneAction( int radius, weight *wgt )
{
	coneAction	*act = new coneAction( wgt, radius );
	eatApp->addAction( act );
	_applyActionOptions( act );
}


void
_crossAction( int radius, weight *wgt )
{
	crossAction	*act = new crossAction( wgt, radius );
	eatApp->addAction( act );
	_applyActionOptions( act );
}


//////////////////////////////////////////////////////////////////////
//  image creation, construction, etc
//
ilImage*
_openImageFile( char *filename )
{
	ilImage *img = new ilFileImg(filename, O_RDONLY );	// no conversions here

	if( img == NULL ) {
	    char	msg[128];
	    sprintf( msg, "image %s: ", filename );
	    perror( msg );
	    return _constImage( 1.0 );
	}

	iflPixel	pixType;
	img->getPixel( 0, 0, pixType );
	switch( pixType.getDataType() ) {
#define	CASE(iltype,minval,maxval)					\
		case iltype:						\
			img->setMinValue( minval );			\
			img->setMaxValue( maxval );			\
			break						
		CASE(iflBit,0,1);
		CASE(iflUChar,0,UCHAR_MAX);
		CASE(iflChar,SCHAR_MIN,SCHAR_MAX);
		CASE(iflUShort,0,USHRT_MAX);
		CASE(iflShort,SHRT_MIN,SHRT_MAX);
		CASE(iflULong,0,ULONG_MAX);
		CASE(iflLong,LONG_MIN,LONG_MAX);
		CASE(iflFloat,0.0,1.0);
		CASE(iflDouble,0.0,1.0);
#undef	CASE
	}
	printf( "open: min = %g, max = %g\n", img->getMinValue(), img->getMaxValue() );
	return img;
}

ilImage*
_scaleImage( double s, ilImage *inImg )
{
	iflPixel	pix( iflDouble, 1, &s );
	ilImage *outImg = new ilMultiplyImg( inImg, new ilConstImg( pix ) );
	printf( "scale: min = %g, max = %g\n", outImg->getMinValue(), outImg->getMaxValue() );
	return outImg;
}

ilImage*
_zoomImageToFit( ilImage *inImg )
{
	ilImage *outImg = new ilRotZoomImg( inImg ); 
	eatApp->addZoomToFit( outImg );
	return outImg;
}

ilImage*
_zoomImage( ilImage *inImg, double zx, double zy )
{
	ilImage *outImg = new ilRotZoomImg( inImg, 0.0, zx, zy, ilBiLinear ); 
	printf( "zoom: min = %g, max = %g\n", outImg->getMinValue(), outImg->getMaxValue() );
	return outImg;
}



//////////////////////////////////////////////////////////////////////
//  image operators
//

ilImage*
_blurImage( ilImage *inImg, double blur, double rad )
{
    ilImage *outImg;
    if( blur == DEFAULT_VALUE ) {
	outImg = new ilBlurImg( inImg );
	printf( "ilBlurImg( * )\n" );
    } else if( rad == DEFAULT_VALUE ) {
        outImg = new ilBlurImg( inImg, blur );
	printf( "ilBlurImg( *, %g )\n", blur );
    } else {
	outImg = new ilBlurImg( inImg, blur, rad );
	printf( "ilBlurImg( *, %g, %g )\n", blur, rad );
    }
    return outImg;
}

ilImage*
_compassImage( ilImage *inImg, double angle )
{
    ilImage *outImg = new ilCompassImg( inImg, angle );
    printf( "compass: min = %g, max = %g\n", outImg->getMinValue(), outImg->getMaxValue() );
    return outImg;
}


ilImage*
_constImage( double value )
{
    iflPixel fillPix( iflDouble, 1, &value );
    ilImage *outImg = new ilConstImg( fillPix );
    return outImg;
}

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
_robertsImage( ilImage *inImg, double bias )
{
    ilImage *outImg;
    if( bias == DEFAULT_VALUE )
        outImg = new ilRobertsImg( inImg );
    else
        outImg = new ilRobertsImg( inImg, bias );
    printf( "roberts: min = %g, max = %g\n", outImg->getMinValue(), outImg->getMaxValue() );
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
	return new weight( w );
}

weight*
_imageWeight( ilImage *img )
{
	return new imageWeight( img );
}

weight*
_contourWeight( weight *contour, weight *scale, double dropoff )
{
    return new contourWeight( contour, scale, dropoff );
}

weight*
_gradWeight( weight *delx, weight *dely )
{
    return new gradWeight( delx, dely );
}

weight*
_lastdirWeight( weight */* dirWt */, weight */* offDirWt */ )
{
	abort();
	return NULL;
}





