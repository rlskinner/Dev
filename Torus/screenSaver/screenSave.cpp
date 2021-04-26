//
//  screen saver using TorusAttractor and TorusTiler
//

#include	<TorusAttractor.h>
#include	<TorusTiler.h>
#include	<hilbertColorSequence.h>
#include	<spaceSampler.h>

#include	<Timer.h>
#include	<getopt.h>

#include	<gl/gl.h>
#include	<gl/device.h>
#include	<math.h>
#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>

float	torusParameterBounds[2][3] =
		{
			{ 0.0, 0.0, 0.5 },	// lower, omega[12], epsilon
			{ 1.0, 1.0, 3.0 },	// upper, omega[12], epsilon
		};

//
//  configurable parameters
//
int     numIterations = 10000;
float	paramStepSize = .05;
float	tileScale = 2.0;
int	tileSize = 256;

void
printUsage( char *program )
{
    fprintf( stderr, "Invalid command option.\n" );
    fprintf( stderr, "Usage: %s [-s %%f] [-n %%d] [-t %%f] [-T %%d] [-S|-D]\n", 
				program );
    fprintf( stderr, 
	"\t-s:  step size through attractor step size [.01]\n"
        "\t-n:  number of points to draw attractor [10000]\n"
        "\t-t:  size of sine lookup tables (X size of a tile) [2.0]\n"
        "\t-T:  size of the attractor in pixels [256]\n"
        "\t-S:  single buffer drawing -- makes attractor transition smoother\n"
        "\t-D:  double buffer drawing -- makes each attractor image sharper\n"
    );
}

int
parseInputArgs( int argc, char *argv[] )
{
    char	*program = argv[0];
    int		c;
    int		singleFlagSet = 0;
    int		doubleFlagSet = 0;

    while( (c = getopt( argc, argv, "s:n:t:T:SD" )) != EOF ) {
	switch( c ) {
	    case 's':
		{
		float	step = atof( optarg );
		if( step > 0.0 ) {
		    paramStepSize = step;
		} else {
		    fprintf( stderr, 
			"warning: parameter step size must be positive\n" );
		    fprintf( stderr, 
			"using default value of %g\n", paramStepSize );
		} 
		}
		break;
	    case 'n':
		{
		int	numPoints = atoi( optarg );
		if( numPoints > 0 ) {
		    numIterations = numPoints;
		} else {
		    fprintf( stderr, 
			"warning: number of points must be positive\n" );
		    fprintf( stderr, 
			"using default value of %d\n", numIterations );
		}
		}
		break;
	    case 't':
		{
		float	scale = atof( optarg );
		if( scale > 0.0 ) {
		    tileScale = scale;
		} else {
		    fprintf( stderr,
			"warning: the tile scale must be positive\n" );
		    fprintf( stderr,
			"using default value of %f\n", tileScale );
		}
		}
		break;
	    case 'T':
		{
		int	size = atoi( optarg );
		if( size > 0 ) {
		    tileSize = size;
		} else {
		    fprintf( stderr, 
			"warning: tile size must be positive\n" );
		    fprintf( stderr, 
			"using default value of %d\n", tileSize );
		}
		}
		break;
	    case 'S':
		if( !doubleFlagSet ) {
		    singleFlagSet = 1;
		} else {
		    fprintf( stderr,
			"warning: can't set single (-S) and double (-D) buffer"
			"drawing modes\n" );
		    fprintf( stderr,
			"ignoring -S option\n" );
		}
		break;
	    case 'D':
		if( !singleFlagSet ) {
		    doubleFlagSet = 1;
		} else {
		    fprintf( stderr,
			"warning: can't set single (-S) and double (-D) buffer"
			"drawing modes\n" );
		    fprintf( stderr,
			"ignoring -D option\n" );
		}
		break;
		
	    case '?':
	    default:
		printUsage( program );
		return 1;
	}
    }
    return 0;
}


int
main( int argc, char *argv[] )
{
    if( parseInputArgs( argc, argv ) ) {
	return( 1 );
    }

    float	colorStep = 1.0/32;		// don't configure this

    spaceSampler torusParamSampler( paramStepSize, 3 );
    torusParamSampler.setBounds( torusParameterBounds[0], 
				 torusParameterBounds[1] );
    HilbertColorSequence colorSequence( colorStep );

    //
    // set up for 640x512 pixels, 5x4 tiling
    //
    foreground();
    prefposition( 0, 1279, 0, 1023 );
    winopen( "Chaos Morph" );
    RGBmode();
    // doublebuffer();
    gconfig();

    ortho2(-0.5,1280-0.5,-0.5,1024-0.5);	// XXX need to get screenres
    cpack( 0xff000000 );
    clear();

    int numColumns = 1280/tileSize;		// let it truncate for now
    int numRows = 1024/tileSize;

    TorusAttractor	attractor( int(tileScale*tileSize), 
				   int(tileScale*tileSize) );
    TorusTiler		tiler( tileSize, tileSize, numColumns, numRows );

    tiler.setBackgroundColor( 0xff000000 );	// black

    while( 1 ) {
	
	//
	//  print out contents of event queue for now
	//
	while( qtest() ) {
	    short	data;
	    long	event = qread( &data );
	    // printf( "event = %d, data = %d\n", event, data );
	    if( event == REDRAW ) {
		attractor.randomizeArrays();
	    }
	}

	float	parameters[3];
	torusParamSampler.getSample( parameters );
	
	attractor.setOmega1( parameters[0] );
	attractor.setOmega2( parameters[1] );
	attractor.setEpsilon( parameters[2] );

	unsigned long	color;
	colorSequence.getABGRColor( color );
	tiler.setDrawingColor( color );

	float	frameTime = tiler.drawTiledImage( numIterations, &attractor );

	++torusParamSampler;
	++colorSequence;
    }

}


