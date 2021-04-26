#include	<stdio.h>
#include	<stdlib.h>
#include	<libc.h>
#include	<unistd.h>
#include	<string.h>
#include	<fcntl.h>
#include	<limits.h>

#include	"image.h"

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

#if	0
ilImage*
_zoomImageToFit( ilImage *inImg )
{
	ilImage *outImg = new ilRotZoomImg( inImg ); 
	eatApp->addZoomToFit( outImg );
	return outImg;
}
#endif	// 0

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

