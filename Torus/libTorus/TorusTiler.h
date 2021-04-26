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

		void	setDrawingColor( unsigned long c ) 	{ drawingColor = c; }
		void	setBackgroundColor( unsigned long c ) 	{ backgroundColor = c; }

		void	setNumIterations( int _numIterations ) 
			{ numIterations = _numIterations; maxIntensity = -1; }
		void	setMaxIntensity( int _maxIntensity ) 
			{ maxIntensity = _maxIntensity; numIterations = -1; }

		virtual float	drawTiledImage( TorusAttractor *torus ) = 0;

	protected:
		double	lastTheta, lastPsi;	// remember previous frame's theta, psi 
		int		numIterations;		// these also trigger the drawing mode
		int		maxIntensity;		

		struct Point {
			short	x, y;
		} 		*pointList;
		int		pointListSize;
		virtual void	resizePointList();

		unsigned long	*intLUT;
		int		LUTsize;

		virtual void	init();
		virtual void	initLUT();

		void	beginFrame();		// do generic setup operations before drawing
		void	endFrame();		// do generic operations after drawing points.

// 		virtual void	drawTiledPoint( int x, int y, unsigned long color ) = 0;	// draw (tiled) point
		int		drawPoint( int iter, int x, int y );	// draw if not already drawn
		// drawing routines subclass must reimplement
		virtual void	beginDrawingFrame() = 0; // do setup operations before drawing
		virtual void	beginDrawingPoints() = 0;
		virtual void	endDrawingPoints() = 0;
		virtual int		drawPoint(int x, int y) = 0; // draw a point
		virtual int		setColor(unsigned long) = 0; // set point color
		virtual void	copyRect(int srcX, int srcY, 
								 int width, int height, 
								 int destX, int destY) = 0;
		virtual void	endDrawingFrame() = 0; // do operations after drawing points.

		int		openBeginEndPoint;

		unsigned long	drawingColor;		// RRGGBBAA packed drawing color
		unsigned long	backgroundColor;	// packed background color

		int		tileWidth, tileHeight;	// tile size
		int		numColumns, numRows;		// tiling factors

		int		numTiles;

		char	*cellStates;		// state flags for drawing efficiently
		int		getCellIndex( int i, int j )	{ return j*tileWidth + i; }
		virtual void	beginFrameStates();
		virtual void	endFrameStates();

};
#endif	/* _TORUSTILER_H__ */
