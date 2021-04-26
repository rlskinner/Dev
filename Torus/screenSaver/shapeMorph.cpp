//
//  make shapes dance
//	RS. 9/27/94
//

#include	<GraphicsApp.h>
#include	"circleShape.h"
#include	"gridShape.h"

#include        <TorusAttractor.h>
#include        <hilbertColorSequence.h>
#include        <spaceSampler.h>
#include	<interval.h>

#include	<getopt.h>

#include	<stdio.h>
#include	<string.h>
#include	<stdlib.h>

class	ShapeMorph : public GraphicsApp {
public:
		ShapeMorph();
    virtual	~ShapeMorph();

    virtual	void	doFrame();
    virtual	void	redraw();

    virtual	int	parseArgs( int argc, char *argv[] );
    virtual	void	init();

protected:
    Interval	omega1Range;
    Interval	omega2Range;
    Interval	epsilonRange;

    Interval	thetaRange, psiRange;	// range of shape's coords

    //
    //  configurable parameters
    //
    char	*shapeName;
    float	paramStepSize;		// step size in param space
    int		complexity;		// complexity of shape, NOT # of points
    int		numIterations;		// number of attractor iterations
    int		numShapes;		// number of old shapes to draw
    float	fade;			// fade color each cycle

    //
    //  objects that actually get work done
    //
    spaceSampler		*torusParamSampler;
    HilbertColorSequence	*colorSequence;
    Shape	*shape;
    TorusAttractor	*attractor;

    void		setView();

    virtual     void    printUsage();


};

Application*
makeDefaultApplication()
{
    return new ShapeMorph;
}

ShapeMorph::ShapeMorph()
    : omega1Range( 0.0, 1.0 ),
      omega2Range( 0.0, 1.0 ),
      epsilonRange( 0.5, 3.0 )
{
    shapeName = strdup( "circle" );
    paramStepSize = .05;
    numIterations = 2;
    fade = 0.95;
    numShapes = 10;
    complexity = -1;			// --> not set

    shape = NULL;
    attractor = NULL;
    torusParamSampler = NULL;
    colorSequence = NULL;
}

ShapeMorph::~ShapeMorph()
{
    delete shapeName;
    delete shape;
    delete attractor;
    delete torusParamSampler;
    delete colorSequence;
}


void
ShapeMorph::printUsage()
{
    fprintf( stderr, "Invalid command option.\n" );
    fprintf( stderr, "Usage: %s [-s %%s] [-p %%f] [-c %%d] [-i %%d] [-f %%f] [-n %%d]\n",
			name );
    fprintf( stderr,
	"\t-s:  shape name, one of circle, grid [circle]\n"
	"\t-p:  parameter step size [0.01]\n"
	"\t-c:  shape complexity (default varies with shape)\n"
	"\t-i:  number of iterations of attractor [2]\n"
	"\t-f:  amount to fade color of each shape [0.95]\n"
	"\t-n:  number of old shapes to draw [10]\n"
    );
}


int
ShapeMorph::parseArgs( int argc, char *argv[] )
{
    int	c;

    setName( argv[0] );
    while( (c = getopt( argc, argv, "s:p:c:i:f:n:" )) != EOF ) {
	switch( c ) {
	    case 's':
		if( shapeName )
		    delete shapeName;
		shapeName = strdup( optarg );
		break;
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
	    case 'c':
	    {
		int	comp = atoi( optarg );
		if( comp > 0 ) {
		    complexity = comp;
		} else {
		    fprintf( stderr, 
			"warning: complexity must be positive, ignored\n" );
		}
	    }
	    break;
	    case 'i':
	    {
		int	iter = atoi( optarg );
		if( iter > 0 ) {
		    numIterations = iter;
		} else {
		    fprintf( stderr, 
			"warning: number of iterations must be positive\n" );
		    fprintf( stderr, 
			"using default value of %d\n", numIterations );
		}
	    }
	    break;
	    case 'f':
	    {
		float	fadeFactor = atof( optarg );
		if( fadeFactor > 0.0 && fadeFactor <= 1.0 ) {
		    fade = fadeFactor;
		} else {
		    fprintf( stderr, 
			"warning: fade factor must be positive and less than 1.0\n" );
		    fprintf( stderr, 
			"using default value of %g\n", fade );
		}
	    }
	    break;
	    case 'n':
	    {
		int	num = atoi( optarg );
		if( num > 0 ) {
		    numShapes = num;
		} else {
		    fprintf( stderr, 
			"warning: number of shapes must be positive\n" );
		    fprintf( stderr, 
			"using default value of %d\n", numShapes );
		}
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
ShapeMorph::init()
{
    if( strcmp( shapeName, "circle" ) == 0 ) {
	shape = new CircleShape;
    } else if( strcmp( shapeName, "grid" ) == 0 ) {
	shape = new GridShape;
    } else {
	return;
    }
    if( complexity > 0 )
	shape->setComplexity( complexity );
    shape->setNumIterations( numIterations );
    shape->setNumShapes( numShapes );
    shape->setColorFade( fade );
    shape->init( thetaRange, psiRange );

    //
    //  create samplers for the parameter and color spaces
    //
    float	colorStep = 1.0/32;		// don't configure this
    colorSequence = new HilbertColorSequence( colorStep );

    float	lowerParamBounds[3], upperParamBounds[3];
    lowerParamBounds[0] = omega1Range.getMin();
    lowerParamBounds[1] = omega2Range.getMin();
    lowerParamBounds[2] = epsilonRange.getMin();
    upperParamBounds[0] = omega1Range.getMax();
    upperParamBounds[1] = omega2Range.getMax();
    upperParamBounds[2] = epsilonRange.getMax();
    torusParamSampler = new spaceSampler( paramStepSize, 3 );
    torusParamSampler->setBounds( lowerParamBounds, upperParamBounds );

    //
    //  do graphics initialization
    //
    long        xPixels = getMaxXPixelSize();
    long        yPixels = getMaxYPixelSize();

    //
    // set up for full screen,
    //  and clear screen to black
    //
    foreground();
    prefposition( 0, xPixels-1, 0, yPixels-1 );
    winopen( "Chaos Morph" );
    RGBmode();
    doublebuffer();
    gconfig();

    ortho2(0.0, 1.0, 0.0, 1.0 );
    cpack( 0xff000000 );
    clear();

    attractor = new TorusAttractor;
    attractor->noWrapMap();

    setView();
}


void
ShapeMorph::doFrame()
{
    cpack( 0xff000000 );
    clear();

    float	parameters[3];
    torusParamSampler->getSample( parameters );
    
    attractor->setOmega1( parameters[0] );
    attractor->setOmega2( parameters[1] );
    attractor->setEpsilon( parameters[2] );

    unsigned long	color;
    colorSequence->getABGRColor( color );
#if	0
    cpack( color );
    bgnline();
    float	v[2];
    v[0] = theta.getMin();	v[1] = psi.getMin();	v2f( v );
    v[0] = theta.getMin();	v[1] = psi.getMax();	v2f( v );
    v[0] = theta.getMax();	v[1] = psi.getMax();	v2f( v );
    v[0] = theta.getMax();	v[1] = psi.getMin();	v2f( v );
    v[0] = theta.getMin();	v[1] = psi.getMin();	v2f( v );
    endline();
#endif	/* 0 */

    shape->draw( attractor, color );
    swapbuffers();

    torusParamSampler->stepSample();
    colorSequence->stepColor();
}


void
ShapeMorph::setView()
{
    attractor->computeRanges( numIterations, 
				omega1Range, omega2Range, epsilonRange,
				thetaRange, psiRange );

    // now define the ortho view to fit the theta/psi without distortion
    float screenAspect = float(getMaxXPixelSize())/float(getMaxYPixelSize());
    float dataAspect = (thetaRange.getMax() - thetaRange.getMin()) / 
			(psiRange.getMax() - psiRange.getMin());
    
    Coord left, right, bottom, top;
    if( dataAspect > screenAspect ) {
	left = thetaRange.getMin();
	right = thetaRange.getMax();
	float	thetaSize = thetaRange.getMax() - thetaRange.getMin();
	float	psiCenter = (psiRange.getMax() + psiRange.getMin())/2.0;
	bottom = psiCenter - thetaSize*screenAspect/2.0;
	top = psiCenter + thetaSize*screenAspect/2.0;
    } else {
	bottom = psiRange.getMin();
	top = psiRange.getMax();
	float	psiSize = psiRange.getMax() - psiRange.getMin();
	float	thetaCenter = (thetaRange.getMax() + thetaRange.getMin())/2.0;
	left = thetaCenter - (psiSize/screenAspect)/2.0;
	right = thetaCenter + (psiSize/screenAspect)/2.0;
    }
    ortho2( left, right, bottom, top );
}

void
ShapeMorph::redraw()
{
    attractor->randomizeArrays();
    setView();
    doFrame();
}


