//
//  An ADT that knows how to tile the Torus attractor into a
//      a graphics window.
//

#include	"oglTorusTiler.h"
#include	"TorusAttractor.h"

#include	<Timer.h>

#include	<GL/gl.h>
#include	<GL/glx.h>
#include	<string.h>

const	char	CellNotDrawn = 0;
const	char	CellDrawn = 1;

oglTorusTiler::oglTorusTiler( int _tileWidth, int _tileHeight )
{
    tileWidth = _tileWidth;
    tileHeight = _tileHeight;
    setTiling( 1, 1 );

    cellStates = new char[tileWidth*tileHeight];
    memset( cellStates, CellNotDrawn, tileWidth*tileHeight );

    lastTheta = 0.0;
    lastPsi = 0.0;

    // doublebuffer();
    // gconfig();
    // reshapeviewport();
}


oglTorusTiler::~oglTorusTiler()
{
    delete cellStates;
}


void
oglTorusTiler::setTiling( int _numColumns, int _numRows )
{
    numColumns = _numColumns;
    numRows = _numRows;
    numTiles = numColumns*numRows;
}

void
oglTorusTiler::setDrawingColor( GLfloat r, GLfloat g, GLfloat b )
{
    drawingColor[0] = 255.0*r;
    drawingColor[1] = 255.0*g;
    drawingColor[2] = 255.0*b;
}

void
oglTorusTiler::setBackgroundColor( GLfloat r, GLfloat g, GLfloat b )
{
    backgroundColor[0] = 255.0*r;
    backgroundColor[1] = 255.0*g;
    backgroundColor[2] = 255.0*b;
}


float
oglTorusTiler::drawTiledImage( int numIterations, TorusAttractor *attractor )
{
    Timer	startFrameTime;
    startFrameTime.mark();

    double	theta = lastTheta;
    double	psi = lastPsi;
    beginFrame();
    for( int iteration = 0; iteration<numIterations; iteration++ ) {
	double	newTheta, newPsi;		// save for debugging
	attractor->mapPoint( theta, psi, &newTheta, &newPsi );

	int	xCell = int(newTheta*tileWidth);
	int	yCell = int(newPsi*tileHeight);

	drawPoint( xCell, yCell );

	theta = newTheta;
	psi = newPsi;
    }
    endFrame();

    lastTheta = theta;
    lastPsi = psi;

    Timer	endFrameTime;
    endFrameTime.mark();
    float frameTime = endFrameTime.diff( startFrameTime );

    return frameTime;
}


void
oglTorusTiler::beginFrameStates()
{
    memset( cellStates, CellNotDrawn, tileWidth*tileHeight );
}

//
// do setup operations before drawing
//
void	
oglTorusTiler::beginFrame()
{
    // cpack( backgroundColor );
    // clear();
    // cpack( drawingColor );
    // bgnpoint();				// start drawing points
    glClear( GL_COLOR_BUFFER_BIT );
    glColor4ubv( drawingColor );
    glBegin( GL_POINTS );
    beginFrameStates();
}


//
// draw (tiled) point
//	if it hasn't already been drawn
//
void	
oglTorusTiler::drawPoint( int x, int y )
{
    int	stateIndex = getCellIndex( x, y );
    if( cellStates[stateIndex] == CellNotDrawn ) {
	cellStates[stateIndex] = CellDrawn;	// flag this cell drawn, 

	glVertex2s( x, y );

    } else {
	// Cell already drawn, do nothing
    }
}


void	
oglTorusTiler::endFrameStates()
{
}


//
// do operations after drawing points.
//
void	
oglTorusTiler::endFrame()
{
    // endpoint();				// end drawing points
    glEnd();				// end drawing points
    for( int i=0; i<numColumns; i++ ) {
	for( int j=0; j<numRows; j++ ) {
	    if( !(i == 0 && j == 0) ) {
		// rectcopy( 0, 0, tileWidth-1, tileHeight-1,
		// 	i*tileWidth, j*tileHeight );
		glRasterPos2i( i*tileWidth, j*tileHeight );
		glCopyPixels( 0, 0, tileWidth-1, tileHeight-1, GL_COLOR );
	    }
	}
    }

    endFrameStates();
}



