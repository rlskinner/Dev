//
//  screen saver using TorusTableAttractor and TorusTiler
//	Displays the attractor, tiled into the screen
//

#include	<GraphicsApp.h>

#include	<TorusTableAttractor.h>
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


class	AttractorMorph : public GraphicsApp {
public:
		AttractorMorph();
    virtual	~AttractorMorph();

    virtual	void	doFrame();
    virtual	void	redraw();

    virtual	int     parseArgs( int argc, char *argv[] );
    virtual     void    init();
protected:
    float	torusParameterBounds[2][3];	// range of omega1, 2, epsilon

    //
    //  configurable parameters
    //
    int     	numIterations;			// # of attractor iterations
    float	paramStepSize;			// step size in param space
    float	tileScale;			// size of lookup table
    int		tileSize;			// size of tile in pixels
    int		maxIntensity;			// # of hits to stop

    //
    //  objects that actually get work done
    //
    spaceSampler		*torusParamSampler;
    HilbertColorSequence	*colorSequence;
    TorusTableAttractor		*attractor;
    TorusTiler			*tiler;

    void	printUsage();
};

Application*
makeDefaultApplication()
{
    return new AttractorMorph;
}

AttractorMorph::AttractorMorph()
{
    //
    //  0 <= omega1, omega2 <= 1
    //  1.0 <= epsilon <= 3
    //
    torusParameterBounds[0][0] = 0.0; torusParameterBounds[1][0] = 1.0;
    torusParameterBounds[0][1] = 0.0; torusParameterBounds[1][1] = 1.0;
    torusParameterBounds[0][2] = 1.0; torusParameterBounds[1][2] = 3.0;

    //
    //  configurable parameters
    //
    numIterations = 10000;
    maxIntensity = -1;
    paramStepSize = .05;
    tileScale = 2.0;
    tileSize = 256;

    attractor = NULL;
    tiler = NULL;
    torusParamSampler = NULL;
    colorSequence = NULL;
}

AttractorMorph::~AttractorMorph()
{
    delete attractor;
    delete tiler;
    delete torusParamSampler;
    delete colorSequence;
}


void
AttractorMorph::printUsage()
{
    fprintf( stderr, "Invalid command option.\n" );
    fprintf( stderr, "Usage: %s [-p %%f] [-n %%d] [-t %%f] [-T %%d] [-S|-D]\n", 
				name );
    fprintf( stderr, 
	"\t-p:  step size through attractor step size [.01]\n"
        "\t-n:  number of points to draw attractor [10000]\n"
        "\t-i:  max intensity of any cell to stop[10000]\n"
        "\t-t:  size of sine lookup tables (X size of a tile) [2.0]\n"
        "\t-T:  size of the attractor in pixels [256]\n"
        "\t-S:  single buffer drawing -- makes attractor transition smoother\n"
        "\t-D:  double buffer drawing -- makes each attractor image sharper\n"
    );
}

int
AttractorMorph::parseArgs( int argc, char *argv[] )
{
    int		c;
    int		singleFlagSet = 0;
    int		doubleFlagSet = 0;

    setName( argv[0] );
    while( (c = getopt( argc, argv, "p:n:i:t:T:SD" )) != EOF ) {
	switch( c ) {
	    case 'p':
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
	    case 'i':
		{
		int	numIntensities = atoi( optarg );
		if( numIntensities > 0 && numIntensities <= 255 ) {
		    maxIntensity = numIntensities;
		} else {
		    fprintf( stderr, 
			"warning: max intensity must be >0 and <=255\n" );
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
		printUsage();
		return 1;
	}
    }
    return 0;
}


void
AttractorMorph::init()
{
    //
    //  create samplers for the parameter and color spaces
    //
    float	colorStep = 1.0/32;		// don't configure this
    colorSequence = new HilbertColorSequence( colorStep );
    torusParamSampler = new spaceSampler( paramStepSize, 3 );
    torusParamSampler->setBounds( torusParameterBounds[0], 
				 torusParameterBounds[1] );

    //
    //  do graphics initialization
    //
    long	xPixels = getMaxXPixelSize();
    long	yPixels = getMaxYPixelSize();

    //
    // set up for full screen,
    //	and clear screen to black
    //
    foreground();
    prefposition( 0, xPixels-1, 0, yPixels-1 );
    winopen( "Chaos Morph" );
    RGBmode();
    // doublebuffer();
    gconfig();

    ortho2(-0.5,xPixels-0.5,-0.5,yPixels-0.5);
    cpack( 0xff000000 );
    clear();

    //
    //  calculate tiling, given screen size and tile size
    //
    long numColumns = xPixels/tileSize;		// let it truncate for now
    long numRows = yPixels/tileSize;

    //
    //  create the attractor function and a tiler for it
    //
    attractor = new TorusTableAttractor( int(tileScale*tileSize), 
				   int(tileScale*tileSize) );
    tiler = new TorusTiler( tileSize, tileSize, int(numColumns), int(numRows) );
    tiler->setBackgroundColor( 0xff000000 );	// black
    if( maxIntensity > 0 ) {
	tiler->setMaxIntensity( maxIntensity );
    } else {
	tiler->setNumIterations( numIterations );
    }
}


void
AttractorMorph::doFrame()
{
    float	parameters[3];
    torusParamSampler->getSample( parameters );
    
    attractor->setOmega1( parameters[0] );
    attractor->setOmega2( parameters[1] );
    attractor->setEpsilon( parameters[2] );

    unsigned long	color;
    colorSequence->getABGRColor( color );
    tiler->setDrawingColor( color );

    float	frameTime = tiler->drawTiledImage( attractor );

    torusParamSampler->stepSample();
    colorSequence->stepColor();
}


void
AttractorMorph::redraw()
{
    cpack( 0xff000000 );
    clear();
    swapbuffers();
    attractor->randomizeArrays();
    doFrame();
}




