/*

Attractors on a torus, as described in the article "Attractors on an
N-Torus: Quasiperiodicity Versus Chaos," by Grebogi, Ott and Yorke,
Physica D, Vol. 15, pp. 354-373 (1985).

The surface of the torus has been unfolded and flattened onto the plane
of the screen, so it is shown as a square.  Points in the square are
referred to by the pair (theta,psi), where theta is the horizontal axis
and psi is vertical.  An attractor is drawn by taking an arbitrary point
and repeatedly putting it through a non-linear mapping, plotting each
new value.

  omega (left button)     - translation factor in mapping
  epsilon (middle button) - amount of non-linearity
  P1 & P2 (right button)  - random non-linear map

This program is a much modified version of "smoke" written by Paul Haeberli,
which in turn is based on the article "A Note on Rendering 3-D Strange
Attractors" from Computers and Graphics Vol 12, No 2. pp. 263-267, 1988.

Greg Turk, April 1991

*/


#include <sys/types.h>
#include <malloc.h>
#include <math.h>
#include <gl/gl.h>
#include <stdlib.h>
#include <unistd.h>

#include	<strToArgs.h>

#include	<ctype.h>
#include	<bstring.h>
#include "torus.h"



/* 
 *  program behavior constants
 */
int	tileFactor = 2;			/* tiling of torus space */
int	omegaSampleRate = 1;		/* sampling of omega w/in one torus */
int	maxCellCount = 255;
unsigned long	pixelScale = 0x010101;	
unsigned long	pixelOffset = 0x000000;	

float	omegaZoom = 2;
float	omegaWindowSize = .001;

double	theta,psi;
int	iSample, jSample;		/* tile we are doing */

int	torusSize = 256;		/* size of torus in pixels */
int	tileSize = 256;			/* size of torus in pixels */
int	winSize = 2*256;		/* size of window */


unsigned long *pixels = NULL;		/* window pixel buffer */
unsigned char *cells = NULL;		/* cell population buffer */
size_t	numPixels;			/* number of pixels */
size_t	numCells;			/* number of cells */
// int count;				/* number of iterations */


//
//  define a macro to do a tiling index
//	arraySize:	(minor) dimension of array
//	tileSize:	(square) dimension of a subtile
//	iTile, jTile:	tile index, which tile
//	i, j:		sub-tile index variables
//
#define	TILE_INDEX(arraySize,tileSize,iTile,jTile,i,j)	\
	arraySize*(jTile*tileSize+j)+iTile*tileSize+i


void
pasteTile( int ip, int jp )
{
    int	itt = ip % omegaSampleRate;
    int	jtt = jp % omegaSampleRate;
    for( int j=0; j<tileSize; j++ ) {
        for( int i=0; i<tileSize; i++ ) {
	    pixels[TILE_INDEX(winSize,tileSize,ip,jp,i,j)] = pixelOffset +
		pixelScale*cells[TILE_INDEX(torusSize,tileSize,itt,jtt,i,j)];
        }
    }
}

#undef	TILE_INDEX

//
//  draw the pixels in pixbuf
//
void
drawAll()
{
    lrectwrite( 0, 0, winSize-1, winSize-1, pixels );
}

//
//	do tileFactor*omegaSampleRate maps, and paste them into
//	the window
//
void
computeMap()
{
    bzero( pixels, numPixels*sizeof(unsigned long) );
    int	sampleNum;
    if( omegaSampleRate == 0 )
	sampleNum = 1;
    else
	sampleNum = tileFactor*omegaSampleRate;

    for( jSample=0; jSample<sampleNum; jSample++ ) {
	for( iSample=0; iSample<sampleNum; iSample++ ) {
	    double	saveO1 = omega1;
	    double	saveO2 = omega2;

	    omega1 += iSample*omegaWindowSize/sampleNum;
	    omega2 += jSample*omegaWindowSize/sampleNum;

	    theta = psi = 0;  /* this initial point is arbitrary */

	    printf( "working on tile %d, %d\n", iSample, jSample );
	    makeMap( cells, torusSize, maxCellCount );
	    pasteTile( iSample, jSample );
	    drawAll();

	    omega1 = saveO1;
	    omega2 = saveO2;
	}
    }
}


void
printHelp()
{
    puts( "" );
    puts( "? prints this message" );
    puts( "t [N] print/set tiling factor" );
    puts( "s [N] print/set omega sampling rate" );
    puts( "o [f f] print/set omega origin" );
    puts( "d [f] print/set omega window size" );
    puts( "m [N] print/set max cell count to quit" );
    puts( "w [N] print/set window size" );
    puts( "g compute new image and display" );
    puts( "r refresh display" );
    puts( "q quit" );
    printf( "\tomega origin = %g %g\n", omega1, omega2 );
    printf( "\tomega sampling rate = %d\n", omegaSampleRate );
    printf( "\tomega window size = %g\n", omegaWindowSize );
    printf( "\tmax cell count = %d\n", maxCellCount );
    printf( "\ttile factor = %d\n", tileFactor );
    printf( "\ttorus size = %d pixels\n", torusSize );
    printf( "\twindow size = %d pixels\n", winSize );
}


void
setSizeParams()
{
    tileSize = int( rint( ceil( winSize/float(tileFactor*omegaSampleRate) ) ) );
    torusSize = tileSize*omegaSampleRate;
    winSize = torusSize*tileFactor;

    prefsize( winSize, winSize );
    winconstraints();
    reshapeviewport();

    delete pixels;
    delete cells;
    numPixels = winSize*winSize;
    pixels = new unsigned long[numPixels];
    numCells = torusSize*torusSize;
    cells = new unsigned char[numCells];
}

void
setWindowSize( int ws )
{
    winSize = ws;
    if( winSize < 32 ) winSize = 32;
    setSizeParams();
}


void
setTileFactor( int tf )
{
    tileFactor = tf;
    if( tileFactor < 1 ) tileFactor = 1;
    setSizeParams();
}

void
setOmegaSampleRate( int sr )
{
    omegaSampleRate = sr;
    if( omegaSampleRate < 1 ) omegaSampleRate = 1;
    setSizeParams();
    // if( omegaSampleRate > 1 ) omegaSampleRate = 1;
}

void
setMaxCellCount( int mcc )
{
    maxCellCount = mcc;
    if( maxCellCount < 1 ) maxCellCount = 1;
    if( maxCellCount > 255 ) maxCellCount = 255;

    // 
    // find a value that will scale 0..maxCellCount to 0..255
    //	for R, G and B at once
    //
    pixelScale = 255/maxCellCount;
    pixelOffset = 255 - pixelScale*maxCellCount;
    pixelScale = (pixelScale << 16) | (pixelScale << 8) | pixelScale;
    pixelOffset = (pixelOffset << 16) | (pixelOffset << 8) | pixelOffset;
}


void
getCommand()
{
	char	inBuf[BUFSIZ];
	gets( inBuf );

	char	**argv;
	int	argc = strToArgs( inBuf, &argv );
	if( argc == 0 ) 
	    return;

	int	errFlag = 0;
	int	c = tolower( argv[0][0] );
	switch( c ) {
	    case 't':
		if( argc == 2 ) {
		    setTileFactor( atoi(argv[1]) );
		    setSizeParams();
		} else if( argc == 1 ) {
		    printf( "\ttile factor = %d\n", tileFactor );
		} else 
		    errFlag = 1;
		break;
	    case 'o':
		if( argc == 3 ) {
		    omega1 = atof(argv[1]);
		    omega2 = atof(argv[2]);
		} else if( argc == 1 ) {
		    printf( "\tomega origin = %g %g\n", omega1, omega2 );
		} else 
		    errFlag = 1;
		break;
	    case 's':
		if( argc == 2 ) {
		    setOmegaSampleRate( atoi(argv[1]) );
		    setSizeParams();
		} else if( argc == 1 ) {
		    printf( "\tomega sampling rate = %d\n", omegaSampleRate );
		} else 
		    errFlag = 1;
		break;
	    case 'd':
		if( argc == 2 ) {
		    omegaWindowSize = atof(argv[1]);
		} else if( argc == 1 ) {
		    printf( "\tomega window size = %g\n", omegaWindowSize );
		} else 
		    errFlag = 1;
		break;
	    case 'm':
		if( argc == 2 ) {
		    setMaxCellCount( atoi(argv[1]) );
		} else if( argc == 1 ) {
		    printf( "\tmax cell count = %d\n", maxCellCount );
		} else 
		    errFlag = 1;
		break;
	    case 'w':
		if( argc == 2 ) {
		    setWindowSize( atoi(argv[1]) );
		} else if( argc == 1 ) {
		    printf( "\twindow size = %d pixels\n", winSize );
		} else 
		    errFlag = 1;
		break;
	    case 'g':
		if( argc == 1 ) {
		    computeMap();
		}
		break;
	    case 'r':
		if( argc == 1 ) {
		    drawAll();
		}
		break;
	    case 'q':
		exit( 0 );
		break;
	    case '?':
		printHelp();
		break;
	    default:
		printf( "*** unrecognized command: %s\n", inBuf );
		break;
	}

	if( errFlag )
	    printHelp();

	freeArgs( argv );
}

void
initGraphics()
{
    prefsize(winSize,winSize);
    if( getenv( "DEBUG" ) )
        foreground();
    winopen("attractors");
    RGBmode();
    gconfig();
    winconstraints();
    clear();
}

int
main()
{
    initGraphics();
    setMaxCellCount( 255 );
    setTileFactor( 2 );
    setOmegaSampleRate( 0 );
    setWindowSize( 2*256 );
    setEpsilon( 0.5 );
    printHelp();
    while( 1 ) {
	getCommand();
    }
}



