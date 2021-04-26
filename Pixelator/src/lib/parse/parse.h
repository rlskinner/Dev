#ifndef	_PARSEIF_H_
#define	_PARSEIF_H_

#define	DEFAULT_VALUE	-98765.4321

#ifdef	__cplusplus

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
void	_diskSeed( int cx, int cy, int rad, weight *wgt );
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
 *  action options
 */
void	_initActionOptions();
void	_setStateOption( int );
void	_setFunctionOption( int );
void	_setWeightOption( int );

/*
 *  weights
 */
weight	*_constWeight( double );
weight	*_imageWeight( ilImage *img );
weight	*_contourWeight( weight *contour, weight *scale, double dropoff );
weight	*_gradWeight( weight *delx, weight *dely );
weight	*_lastdirWeight( weight *dirWt, weight *offDirWt );


#ifdef	__cplusplus
    }
#endif	/* __cplusplus */

#endif	/* _PARSEIF_H_ */

