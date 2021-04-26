#ifndef	_TORUSTILER_OPENGL_H__
#define	_TORUSTILER_OPENGL_H__
//
//  An OpenGL implementation of TorusTiler:  tile the Torus attractor into
//  a a graphics window.
//

#include	<sys/types.h>

#include	"TorusTiler.h"

class	OGLTorusTiler {
	public:
		OGLTorusTiler( int _tileWidth, int _tileHeight, int _numColumns, int _numRows );

		virtual float	drawTiledImage( TorusAttractor *torus );

		// drawing routines subclass must reimplement
		virtual void	beginDrawingFrame(); // do setup operations before drawing
		virtual void	beginDrawingPoints();
		virtual void	endDrawingPoints();
		virtual int		drawPoint(int x, int y); // draw a point
		virtual int		setColor(unsigned long); // set point color
		virtual void	copyRect(int srcX, int srcY, 
								 int width, int height, 
								 int destX, int destY);
		virtual void	endDrawingFrame(); // do operations after drawing points.
};
#endif	/* _TORUSTILER_OPENGL_H__ */
