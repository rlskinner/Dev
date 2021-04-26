//
//  An ADT that knows how to tile the Torus attractor into a
//      a graphics window.
//

#include	"TorusTiler.h"
#include	"TorusAttractor.h"

#include	<Timer.h>

#include	<gl/gl.h>
#include	<string.h>
#include	<stdio.h>

const	char	CellNotDrawn = 0;
const	char	CellOldColor = 1;
const	char	CellNewColor = 2;

TorusTiler::TorusTiler( int _tileWidth, int _tileHeight, 
	    int _numColumns, int _numRows )
{
    tileWidth = _tileWidth;
    tileHeight = _tileHeight;
    numColumns = _numColumns;
    numRows = _numRows;

    numTiles = numColumns*numRows;
    tileOffsets = new cellPosition[numTiles];

    int	tile = 0;
    for( int column=0; column<numColumns; column++ ) {
	for( int row=0; row<numRows; row++ ) {
	    tileOffsets[tile].x = column*tileWidth;
	    tileOffsets[tile].y = row*tileHeight;
	    tile++;
	}
    }

    cellStates = new char[tileWidth*tileHeight];
    memset( cellStates, CellNotDrawn, tileWidth*tileHeight );

    lastPositions = NULL;
    numPositions = 0;

    lastTheta = 0.0;
    lastPsi = 0.0;

    // doublebuffer();
    // gconfig();
    reshapeviewport();
}


TorusTiler::~TorusTiler()
{
    delete tileOffsets;
    delete cellStates;

    delete lastPositions;
}

void
TorusTiler::resizePositionArray( int n )
{
    if( n > numPositions ) {
	if( numPositions > 0 ) {
	    //  'realloc'
	    cellPosition	*newPos = new cellPosition[n];
	    int	i;
	    for( i=0; i<numPositions; i++ ) {
		newPos[i] = lastPositions[i];	// copy old values
	    }
	    for( i=numPositions; i<n; i++ ) {
		newPos[i] = lastPositions[numPositions-1];	// extend last
	    }
	    delete lastPositions;
	    lastPositions = newPos;
	} else {
	    // new allocation, set to 0,0
	    numPositions = n;
	    lastPositions = new cellPosition[numPositions];
	    for( int i=0; i<numPositions; i++ ) {
		lastPositions[i].x = 0;
		lastPositions[i].y = 0;
	    }
	}
    }
}


float
TorusTiler::drawTiledImage( int numIterations, TorusAttractor *attractor )
{
    Timer	startFrameTime;
    startFrameTime.mark();

    resizePositionArray( numIterations );

    double	theta = lastTheta;
    double	psi = lastPsi;
    beginFrame();
    for( int iteration = 0; iteration<numIterations; iteration++ ) {
	attractor->mapPoint( theta, psi, &theta, &psi );

	int	xCell = int(theta*tileWidth);
	int	yCell = int(psi*tileHeight);

	setCell( iteration, xCell, yCell );
	lastPositions[iteration].x = xCell;
	lastPositions[iteration].y = yCell;
    }
    endFrame();

    lastTheta = theta;
    lastPsi = psi;

    Timer	endFrameTime;
    endFrameTime.mark();
    return endFrameTime.diff( startFrameTime );

    // swapbuffers();
}


void
TorusTiler::beginFrameStates()
{
    int	numCells = tileWidth*tileHeight;
    for( int i=0; i<numCells; i++ ) {
	if( cellStates[i] == CellNewColor ) {
	    cellStates[i] = CellOldColor;
	} else if( cellStates[i] == CellOldColor ) {
	    printf( "error, cell is old color\n" );
	} else {
	    // its OK to not be drawn
	}
    }
}

//
// do setup operations before drawing
//
void	
TorusTiler::beginFrame()
{
    beginFrameStates();
}


void
TorusTiler::drawTiledPoint( int x, int y, u_long color )
{
    cpack( color );

    short	v[2];				// and draw it

    bgnpoint();
    for( int i=0; i<numTiles; i++ ) {
	v[0] = x + tileOffsets[i].x;
	v[1] = y + tileOffsets[i].y;
	v2s( v );
    }
    endpoint();
}

//
// draw (tiled) point
//	if it hasn't already been drawn
//
void	
TorusTiler::setCell( int numCell, int x, int y )
{
    //
    //  clean up old position, if it is still old
    //
    int	oldIndex = getCellIndex( lastPositions[numCell].x, 
				 lastPositions[numCell].y );
    if( cellStates[oldIndex] == CellOldColor ) {
	drawTiledPoint( lastPositions[numCell].x, lastPositions[numCell].y,
			backgroundColor );
	cellStates[oldIndex] = CellNotDrawn;
    } else {
	// if its not drawn, don't touch it
	// if it is new, then don't wipe it out!
    }

    //
    //  set new position, if it isn't already set
    //
    int	newIndex = getCellIndex( x, y );
    if( cellStates[newIndex] != CellNewColor ) {
	drawTiledPoint( x, y, drawingColor );
	cellStates[newIndex] = CellNewColor;
    } else {
	// if is already set, then don't bother
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
    endFrameStates();
}



