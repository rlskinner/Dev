#ifndef	_TORUSTILER_H__
#define	_TORUSTILER_H__
//
//  An ADT that knows how to tile the Torus attractor into a 
//	a graphics window.
//

#include	<sys/types.h>
#include	<GL/gl.h>

#include	"TorusAttractor.h"

struct	cellPosition {
	short	x, y;			// cell positions w/in an image
};

class	oglTorusTiler {
public:
    oglTorusTiler( int tileWidth, int tileHeight );
    ~oglTorusTiler();
    
    void	setTiling( int numColumns, int numRows );
    void	setDrawingColor( GLfloat r, GLfloat g, GLfloat b );
    void	setBackgroundColor( GLfloat r, GLfloat g, GLfloat b );

    float	drawTiledImage( int numIterations, TorusAttractor *torus );

private:
    double	lastTheta, lastPsi;	// remember previous frame's theta, psi 

    void	beginFrame();		// do setup operations before drawing
    void	drawTiledPoint( int x, int y, u_long color );	// draw (tiled) point
    void	drawPoint( int x, int y );	// draw if not already drawn
    void	endFrame();		// do operations after drawing points.
    int		openBeginEndPoint;

    GLubyte	drawingColor[3];		// RRGGBBAA packed drawing color
    GLubyte	backgroundColor[3];	// packed background color

    int		tileWidth, tileHeight;	// tile size
    int		numColumns, numRows;		// tiling factors

    int		numTiles;

    char	*cellStates;		// state flags for drawing efficiently
    int		getCellIndex( int i, int j )	{ return j*tileWidth + i; }
    void	beginFrameStates();
    void	endFrameStates();

};
#endif	/* _TORUSTILER_H__ */
