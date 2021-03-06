//
//  An ADT that knows how to tile the Torus attractor into a
//      a graphics window.
//

#include	"TorusTiler.h"
#include	"TorusAttractor.h"

#include	<Timer.h>

#include	<gl/gl.h>
#include	<string.h>

const	char	CellNotDrawn = 0;
const	char	CellDrawn = 1;

TorusTiler::TorusTiler( int _tileWidth, int _tileHeight, 
	    int _numColumns, int _numRows )
{
    tileWidth = _tileWidth;
    tileHeight = _tileHeight;
    numColumns = _numColumns;
    numRows = _numRows;

    numTiles = numColumns*numRows;

    cellStates = new char[tileWidth*tileHeight];
    memset( cellStates, CellNotDrawn, tileWidth*tileHeight );

    lastTheta = 0.0;
    lastPsi = 0.0;

    doublebuffer();
    gconfig();
    reshapeviewport();
}


TorusTiler::~TorusTiler()
{
    delete cellStates;
}


float
TorusTiler::drawTiledImage( int numIterations, TorusAttractor *attractor )
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

    swapbuffers();
    return frameTime;
}


void
TorusTiler::beginFrameStates()
{
    memset( cellStates, CellNotDrawn, tileWidth*tileHeight );
}

//
// do setup operations before drawing
//
void	
TorusTiler::beginFrame()
{
    cpack( backgroundColor );
    clear();
    cpack( drawingColor );
    bgnpoint();				// start drawing points
    beginFrameStates();
}


//
// draw (tiled) point
//	if it hasn't already been drawn
//
void	
TorusTiler::drawPoint( int x, int y )
{
    int	stateIndex = getCellIndex( x, y );
    if( cellStates[stateIndex] == CellNotDrawn ) {
	cellStates[stateIndex] = CellDrawn;	// flag this cell drawn, 

	short	v[2];				// and draw it

	v[0] = x;
	v[1] = y;
	v2s( v );

    } else {
	// Cell already drawn, do nothing
    }
}


void	
TorusTiler::endFrameStates()
{
}


//
// do operations after drawing points.
//
void	
TorusTiler::endFrame()
{
    endpoint();				// end drawing points
    for( int i=0; i<numColumns; i++ ) {
	for( int j=0; j<numRows; j++ ) {
	    if( !(i == 0 && j == 0) ) {
		rectcopy( 0, 0, tileWidth-1, tileHeight-1,
			i*tileWidth, j*tileHeight );
	    }
	}
    }

    endFrameStates();
}



