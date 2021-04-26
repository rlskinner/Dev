//
//  run performance tests on the TorusAttractor and TorusTiler
//	classes
//

#include	<TorusAttractor.h>
#include	<TorusTiler.h>

#include	<Timer.h>
#include	<StandardDeviation.h>

#include	<gl/gl.h>
#include	<math.h>
#include	<stdio.h>

////////////////////////////////////////////////////////////////////

const	double	startOmega1 = 0.486;
const	double	startOmega2 = 0.905;
const	double	startEpsilon = 0.5;
const	double	endOmega1 = 0.721;
const	double	endOmega2 = 0.866;
const	double	endEpsilon = 2.5;
const	int	numFrames = 200;

const	int	numIterations = 10000;

const	float	syncTime = 1.0/60.0;

unsigned long	torusColors[] = {
		    0xff0000ff,	
		    0xff00ffff, 
		    0xff00ff00, 
		    0xffffff00, 
		    0xffff0000, 
		    0xffff00ff, 
		};
const	int	numColors = (sizeof(torusColors)/sizeof(unsigned long));

//
//  perform linear interpolation
//
const	double	linearInterpolate( double a, double b, double t )
{
    return a + t*(b-a);
}

void
doPerformanceTest( int tileWidth, int tileHeight, int numColumns, int numRows )
{
    TorusAttractor	attractor( tileWidth, tileHeight );
    TorusTiler		tiler( tileWidth, tileHeight, numColumns, numRows );

    int	colorNumber = 0;
    tiler.setBackgroundColor( 0xff000000 );	// black

    //
    //  initialize variables for performance measurements
    //
    float	minFrameTime = 0.0;
    float	maxFrameTime = 0.0;
    float	cumulativeFrameTime = 0.0;	// used to compute average
    int		numFramesFasterThan60Hz = 0;

    StandardDeviation	std;			// calculator

    Timer	startIterationsTime;
    startIterationsTime.mark();
    for( int frame=0; frame<numFrames; frame++ ) {

	double	t = float(frame)/(numFrames-1);
	attractor.setOmega1( linearInterpolate( startOmega1, endOmega1, t ) );
	attractor.setOmega2( linearInterpolate( startOmega2, endOmega2, t ) );
	attractor.setEpsilon( linearInterpolate( startEpsilon, endEpsilon, t ));
	tiler.setDrawingColor( torusColors[colorNumber] );
	colorNumber = (colorNumber+1) % numColors;

	Timer	startFrameTime;
	startFrameTime.mark();

	float	frameTime = tiler.drawTiledImage( numIterations, &attractor );

	if( frame != 0 ) {
	    //  compute min/max
	    if( frameTime < minFrameTime ) minFrameTime = frameTime;
	    if( frameTime > maxFrameTime ) maxFrameTime = frameTime;
	} else {
	    //  initialize min/max
	    minFrameTime = frameTime;
	    maxFrameTime = frameTime;
	}
	cumulativeFrameTime += frameTime;
	if( frameTime < syncTime ) numFramesFasterThan60Hz++;
	std.addSample( frameTime );
    }

    Timer	endIterationsTime;
    endIterationsTime.mark();

    float	iterationTime = endIterationsTime.diff( startIterationsTime );
    float	averageFrameTime = iterationTime / numFrames;

    puts( "================================" );
    printf( "performance numbers for %dx%d image, %dx%d tiles\n", 
	    tileWidth, tileHeight, numColumns, numRows );
    printf( "average frame time = %g sec (%g frames/sec)\n", 
	    averageFrameTime, 1.0/averageFrameTime );
    printf( "minimum frame time = %g sec\n", minFrameTime );
    printf( "maximum frame time = %g sec\n", maxFrameTime );
    printf( "frame time standard deviation = %g sec\n", std.getStandardDeviation() );
    printf( "number frames faster than 60Hz = %d\n", numFramesFasterThan60Hz );
}



void
main()
{
    //
    // set up for 640x512 pixels, 5x4 tiling
    //
    foreground();
    prefposition( 0, 639, 1023-511, 1023 );
    winopen( "torus performance test" );
    RGBmode();
    // doublebuffer();
    gconfig();

    ortho2(-0.5,640-0.5,-0.5,512-0.5);
    cpack( 0xff000000 );
    clear();
    doPerformanceTest( 128, 128, 5, 4 );

    //
    //  set up for 1280x1024, 5x4
    //
    prefposition( 0, 1279, 0, 1023 );
    winconstraints();

    reshapeviewport();
    ortho2(-0.5,1280-0.5,-0.5,1024-0.5);
    cpack( 0xff000000 );
    clear();
    doPerformanceTest( 256, 256, 5, 4 );

}


