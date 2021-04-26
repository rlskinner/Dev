#ifndef	_PARSEIF_H_
#define	_PARSEIF_H_

#define	DEFAULT_VALUE	-98765.4321

#ifdef	__cplusplus
#    include        <il/ilBlurImg.h>
#    include        <il/ilCompassImg.h>
#    include        <il/ilConstImg.h>
#    include        <il/ilGenericImgFile.h>
#    include        <il/ilImage.h>
#    include        <il/ilInvertImg.h>
#    include        <il/ilMultiplyImg.h>
#    include        <il/ilNegImg.h>
#    include        <il/ilRobertsImg.h>
#    include        <il/ilRotZoomImg.h>
#    include        <il/ilSharpenImg.h>
#    include        <il/ilThreshImg.h>

#    include        "weight.h"
#    include        "constWeight.h"
#    include        "imageWeight.h"
#    include        "gradWeight.h"

#else	/* __cplusplus */
    typedef	void ilImage;
    typedef	void weight;
#endif	/* __cplusplus */

#ifdef	__cplusplus
    extern	"C" {
#endif	/* __cplusplus */

/*
 *  options, misc
 */
void	_loadColormap( char *file );
void	_setSize( int sx, int sy );
void	_setSizeAt( int sx, int sy, int px, int py );
void	_writeImage( char *file, int type );
void	_exitWhenDone();

/*
 *  seeds
 */
void	_edgeSeed( weight *wgt );
void	_imageSeed( ilImage *img, int fit, double sx, double sy );
void	_lineSeed( double x0, double y0, double x1, double y1, weight *wgt );
void	_randomIntSeed( int num, weight *wgt );
void	_randomPerCentSeed( double percent, weight *wgt );

/*
 *  actions
 */
void	_coneAction( int radius, weight *wgt );
void	_cornerAction( weight *wgt );
void	_crossAction( int radius, weight *wgt );
void	_dirAction( weight *primary, weight *wgt );
void	_edgeAction( weight *wgt );
void	_nborAction( int connectedness, weight *wgt );
void	_ringAction( int radius, weight *wgt );
void	_scatterRingAction( int radius, weight *wgt );

/*
 *  weights
 */
weight	*_constWeight( double );
weight	*_imageWeight( ilImage *img );
weight	*_gradWeight( weight *delx, weight *dely );
weight	*_lastdirWeight( weight *dirWt, weight *offDirWt );

/*
 *  images
 */
ilImage	*_blurImage( ilImage*, double, double );
ilImage *_compassImage( ilImage*, double );
ilImage *_constImage( double );
ilImage	*_invertImage( ilImage* );
ilImage	*_negImage( ilImage* );
ilImage	*_openImageFile( char* );
ilImage *_robertsImage( ilImage*, double );
ilImage	*_scaleImage( double, ilImage* );
ilImage	*_sharpenImage( ilImage*, double, double );
ilImage	*_threshImage( ilImage*, double );
ilImage	*_zoomImage( ilImage*, double, double );
ilImage	*_zoomImageToFit( ilImage* );

#ifdef	__cplusplus
    }
#endif	/* __cplusplus */

#endif	/* _PARSEIF_H_ */

