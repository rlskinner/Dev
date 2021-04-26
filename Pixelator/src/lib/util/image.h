#ifndef	_image_h_
#define	_image_h_

#define	DEFAULT_VALUE	-98765.4321

#ifdef	__cplusplus
#    include        <il/ilBlurImg.h>
#    include        <il/ilCompassImg.h>
#    include        <il/ilConstImg.h>
#    include        <il/ilFileImg.h>
#    include        <il/ilImage.h>
#    include        <il/ilInvertImg.h>
#    include        <il/ilMultiplyImg.h>
#    include        <il/ilNegImg.h>
#    include        <il/ilRobertsImg.h>
#    include        <il/ilRotZoomImg.h>
#    include        <il/ilSharpenImg.h>
#    include        <il/ilThreshImg.h>

#else	/* __cplusplus */
    typedef	void ilImage;
    typedef	void weight;
#endif	/* __cplusplus */

#ifdef	__cplusplus
    extern	"C" {
#endif	/* __cplusplus */

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

#endif	/* _image_h_ */

