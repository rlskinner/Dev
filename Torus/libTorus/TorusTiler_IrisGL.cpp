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
#include	<stdlib.h>
#include	<math.h>

const	char	CellNotDrawn = 0;
const	char	CellDrawn = 1;

const	float	Gamma = 2.0;

TorusTiler::TorusTiler( int _tileWidth, int _tileHeight, 
	    int _numColumns, int _numRows )
{
    tileWidth = _tileWidth;
    tileHeight = _tileHeight;
    numColumns = _numColumns;
    numRows = _numRows;

    numIterations = 1000;
    maxIntensity = -1;

    pointList = NULL;
    pointListSize = 0;
    intLUT = NULL;
    LUTsize = 0;

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


void
TorusTiler::init()
{
    if( maxIntensity > 0 ) {
	// initialize tables for various intensity
	if( NULL == pointList ) {
	    pointListSize = 1000;
	    pointList = (Point *)malloc(pointListSize*sizeof(Point));
	}
	if( NULL == intLUT ) {
	    LUTsize = maxIntensity+1;
	    intLUT = new u_long[LUTsize];
	}
    } else {
	// initialize for binary display
    }
}


void
TorusTiler::initLUT()
{
    if( maxIntensity > 0 ) {
	// printf( "drawingColor = 0x%08x\n", drawingColor );

	for( int i=0; i<maxIntensity; i++ ) {
	    int	rgba[4];
	    rgba[0] = drawingColor & 0x000000ff;
	    rgba[1] = (drawingColor >> 8) & 0x000000ff;
	    rgba[2] = (drawingColor >> 16) & 0x000000ff;
	    rgba[3] = (drawingColor >> 24) & 0x000000ff;

	    float	v = float(i)/(maxIntensity-1);
	    v = fexp( log( v ) / Gamma );	// gamma correct for contrast
	    for( int c=0; c<3; c++ ) {
		rgba[c] = rint(v*rgba[c]);
	    }
	    intLUT[i] = rgba[0] | rgba[1] << 8 | 
			rgba[2] << 16 | rgba[3] << 24; 
	    // printf( "LUT[%d] = 0x%08x\n", i, intLUT[i] );
	}
	intLUT[maxIntensity] = drawingColor;
    }
}


void
TorusTiler::resizePointList()
{
    pointListSize *= 2;
    pointList = (Point*)realloc( pointList, pointListSize*sizeof(Point) );
}


float
TorusTiler::drawTiledImage( TorusAttractor *attractor )
{
    Timer	startFrameTime;
    startFrameTime.mark();

    double	theta = lastTheta;
    double	psi = lastPsi;
    int		quit = FALSE;
    int		iteration = 0; 
    init();
    initLUT();
    beginFrame();
    while( !quit ) {
	double	newTheta, newPsi;		// save for debugging
	attractor->mapPoint( theta, psi, &newTheta, &newPsi );

	int	xCell = int(newTheta*tileWidth);
	int	yCell = int(newPsi*tileHeight);

	int	cellCount = drawPoint( iteration, xCell, yCell );

	theta = newTheta;
	psi = newPsi;
    
	iteration++;

	quit = maxIntensity > 0 ? 
	      cellCount == maxIntensity
	    : iteration == numIterations; 

    }
    numIterations = iteration;
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
int
TorusTiler::drawPoint( int i, int x, int y )
{
    int	stateIndex = getCellIndex( x, y );
    if( maxIntensity > 0 ) {
	cellStates[stateIndex]++;
	if( i >= pointListSize ) {
	    resizePointList();
	}
	pointList[i].x = x;
	pointList[i].y = y;
    } else {
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

    return cellStates[stateIndex];
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
    if( maxIntensity > 0 ) {
	// draw the list of points
	for( int i=0; i<numIterations; i++ ) {
	    int stateIndex = getCellIndex( pointList[i].x, pointList[i].y );
	    if( cellStates[stateIndex] ) {
		cpack( intLUT[cellStates[stateIndex]] );
		short	v[2];
		v[0] = pointList[i].x;
		v[1] = pointList[i].y;
		v2s( v );
		cellStates[stateIndex] = CellNotDrawn;
	    }
	}
    }
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



