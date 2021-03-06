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

    float	drawTiledImage( int numIterations, TorusAttractor *torus );

private:
    double	lastTheta, lastPsi;	// remember previous frame's theta, psi 

    void	beginFrame();		// do setup operations before drawing
    void	drawTiledPoint( int x, int y, u_long color );	// draw (tiled) point
    void	setCell( int numCell, int x, int y );	// set cell if needed
    void	endFrame();		// do operations after drawing points.

    u_long	drawingColor;		// RRGGBBAA packed drawing color
    u_long	backgroundColor;	// packed background color

    int		tileWidth, tileHeight;	// tile size
    int		numColumns, numRows;		// tiling factors

    int		numTiles;
    cellPosition    *tileOffsets;	// precomputed offsets to do tiling

    char	*cellStates;		// state flags for drawing efficiently
    int		getCellIndex( int i, int j )	{ return j*tileWidth + i; }
    void	beginFrameStates();
    void	endFrameStates();

    cellPosition    *lastPositions;	// cell hit in last frame, 
    					//	for each iteration
    int		numPositions;		// size of Position array
    void	resizePositionArray( int n );
};
#endif	/* _TORUSTILER_H__ */
