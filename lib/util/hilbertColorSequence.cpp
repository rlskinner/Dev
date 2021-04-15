//
//  Generate a color sequence that traverses the 3 brightest
//      faces of the color cube in hilbert patterns
//

#include	<hilbertColorSequence.h>
#include	<math.h>
#include	<stdlib.h>
#include	<stdio.h>

//
//  define transformations to convert from 
//	2D Hilbert points into RGB, for each face
//	in the pattern
//
const	int	numberOfColorFaces = 6;		// six in non-repeating pattern
float       faceTransforms[numberOfColorFaces][3][3] = 
	{	// Green constant
	    {
		{  0.0, -1.0,  1.0 }, 	// 1 - J
		{  0.0,  0.0,  1.0 }, 	// 1
		{ -1.0,  0.0,  1.0 }, 	// 1 - I
	    },
		// Red constant
	    {
		{  0.0,  0.0,  1.0 },	// 1
		{  0.0, -1.0,  1.0 },	// 1 - J
		{  1.0,  0.0,  0.0 },	// I
	    },
		// Blue constant
	    {
		{  0.0, -1.0,  1.0 },	// 1 - J
		{ -1.0,  0.0,  1.0 },	// 1 - I
		{  0.0,  0.0,  1.0 },	// 1
	    },
		// Red constant
	    {
		{  0.0,  0.0,  1.0 },	// 1
		{  1.0,  0.0,  0.0 },	// I
		{  0.0, -1.0,  1.0 },	// 1 - J
	    },
		// Green constant
	    {
		{ -1.0,  0.0,  1.0 },	// 1 - I
		{  0.0,  0.0,  1.0 },	// 1
		{  0.0, -1.0,  1.0 },	// 1 - J
	    },
		// Blue constant
	    {
		{  1.0,  0.0,  0.0 },	// I
		{  0.0, -1.0,  1.0 },	// 1 - J
		{  0.0,  0.0,  1.0 },	// 1
	    },
	};

HilbertColorSequence::HilbertColorSequence()
{
    init();
}

HilbertColorSequence::HilbertColorSequence( float step )
{
    init();
    setStepSize( step );
}

void
HilbertColorSequence::init()
{
    hilbertSequence = new HilbertSequence;
    currentHilbertPoint = -1;
    currentFace = -1;
}

HilbertColorSequence::~HilbertColorSequence()
{
    delete hilbertSequence;
}

//
//  set step size.
//	since the hilbert only gives us a power of two, we compute
//	the smallest power of 2, such that 1.0/2**N < stepSize
//	Set the HilbertSequence to that resolution, and addjust our
//	step size accordingly.
//
//  XXX this should really reset the sequence for robustness, but for
//	now we assume that the step size is never set in the middle of 
//	a sequence.
//
void
HilbertColorSequence::setStepSize( float step )
{
    //
    // solve for 1.0/2**N = stepSize
    //
    double	N = log(1.0 / step)/log(2.0);

    //
    // round N up to next integer, so that the real step size will
    // be less than step, and compute the real step size.
    //
    int	hilbertRes = int( ceil( N ) );
    step = 1.0 / pow( 2.0, double(hilbertRes) );
#ifdef	TEST
    printf( "actual step size = %g\t  hilbert resolution = %d\n", 
		step, hilbertRes );
#endif	/* TEST */
    setHilbertResolution( hilbertRes );
    ColorSequence::setStepSize( step );

    currentHilbertPoint = -1;
    currentFace = -1;
}


//
//  set hilbert resolution, and get scaled 
void
HilbertColorSequence::setHilbertResolution( int hilbertRes )
{
    hilbertSequence->setResolution( hilbertRes );
    hilbertSequence->computeSequence();

    numHilbertPoints = hilbertSequence->getSequence( &hilbertPoints );
#ifdef	TEST
    printf( "hilbert sequence has %d points\n", numHilbertPoints );
#endif	/* TEST */

    int	hilbertRange = (1 << hilbertRes) - 1;		// max value in sequence
    hilbertScale = 1.0/hilbertRange;		// scale factor ==> 0-1
}


void
HilbertColorSequence::stepColor()
{

    if( currentFace != -1 ) {		// not initializing
	currentHilbertPoint++;
	if( currentHilbertPoint == numHilbertPoints ) {
	    currentHilbertPoint = 0;	// start at beginning of sequence
	    currentFace++;		// of next face
	    if( currentFace == numberOfColorFaces ) {
		currentFace = 0;	// wrap face sequence
	    }
#ifdef	TEST
	printf( "new face = %d\n", currentFace );
#endif	/* TEST */
	}
    } else {				// this is initial state
	currentFace = 0;
	currentHilbertPoint = 0;
    }

    transformPointToColor( hilbertPoints[currentHilbertPoint], rgb );
}

void
HilbertColorSequence::transformPointToColor( HilbertPoint &point, float _rgb[3] )
{
    float	xPos = point.i * hilbertScale;
    float	yPos = point.j * hilbertScale;

    _rgb[ColorSequence::red] = faceTransforms[currentFace][ColorSequence::red][0]*xPos +
	        faceTransforms[currentFace][ColorSequence::red][1]*yPos +
	        faceTransforms[currentFace][ColorSequence::red][2];
    _rgb[ColorSequence::green] = faceTransforms[currentFace][ColorSequence::green][0]*xPos +
	          faceTransforms[currentFace][ColorSequence::green][1]*yPos +
	          faceTransforms[currentFace][ColorSequence::green][2];
    _rgb[ColorSequence::blue] = faceTransforms[currentFace][ColorSequence::blue][0]*xPos +
	         faceTransforms[currentFace][ColorSequence::blue][1]*yPos +
	         faceTransforms[currentFace][ColorSequence::blue][2];
}


#ifdef	TEST
#include	<gl/gl.h>

int	
main( int argc, char *argv[] )
{
    float	res = .1;
    if( argc > 1 ) {
	res = atof( argv[1] );
    }

    HilbertColorSequence hcs( res );

    foreground();
    prefposition( 0, 100, 800, 900 );
    winopen( "HilbertColorSequence" );
    RGBmode();
    doublebuffer();
    gconfig();

    while( 1 ) {
	unsigned long	rgba;
	hcs.getABGRColor( rgba );
	++hcs;
	cpack( rgba );
	clear();
	swapbuffers();
    }
}

#endif	/* TEST */
