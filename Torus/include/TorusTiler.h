#ifndef	_TORUSTILER_H__
#define	_TORUSTILER_H__
//
//  An ADT that knows how to tile the Torus attractor into a 
//	a graphics window.
//

#include	<sys/types.h>

#include	"TorusAttractor.h"

struct	cellPosition {
	short	x, y;			// cell positions w/in an image
};

class	TorusTiler {
public:
    TorusTiler( int tileWidth, int tileHeight, int numColumns, int numRows );
    ~TorusTiler();
    
    void	setDrawingColor( u_long c ) 	{ drawingColor = c; }
    void	setBackgroundColor( u_long c ) 	{ backgroundColor = c; }

    void	setNumIterations( int _numIterations ) 
    			{ numIterations = _numIterations; maxIntensity = -1; }
    void	setMaxIntensity( int _maxIntensity ) 
    			{ maxIntensity = _maxIntensity; numIterations = -1; }

    float	drawTiledImage( TorusAttractor *torus );

private:
    double	lastTheta, lastPsi;	// remember previous frame's theta, psi 
    int		numIterations;		// these also trigger the drawing mode
    int		maxIntensity;		

    struct Point {
	short	x, y;
    } 		*pointList;
    int		pointListSize;
    void	resizePointList();

    u_long	*intLUT;
    int		LUTsize;

    void	init();
    void	initLUT();

    void	beginFrame();		// do setup operations before drawing
    void	endFrame();		// do operations after drawing points.

    void	drawTiledPoint( int x, int y, u_long color );	// draw (tiled) point
    int		drawPoint( int iter, int x, int y );	// draw if not already drawn
    int		openBeginEndPoint;

    u_long	drawingColor;		// RRGGBBAA packed drawing color
    u_long	backgroundColor;	// packed background color

    int		tileWidth, tileHeight;	// tile size
    int		numColumns, numRows;		// tiling factors

    int		numTiles;

    char	*cellStates;		// state flags for drawing efficiently
    int		getCellIndex( int i, int j )	{ return j*tileWidth + i; }
    void	beginFrameStates();
    void	endFrameStates();

};
#endif	/* _TORUSTILER_H__ */
