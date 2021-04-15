//
//  sample some N dimensional space randomly by firing 
//	vectors into it at random
//

#include	<spaceSampler.h>
#include	<math.h>
#include	<limits.h>
#include	<stdio.h>
#include	<assert.h>

#include "randomUtil.h"

inline float	min( float a, float b ) { return a < b ? a : b; }
inline float	max( float a, float b ) { return a > b ? a : b; }

spaceSampler::spaceSampler( float step, int _ndim )
{
    init( step, _ndim );

    float	*low = new float[ndim];
    float	*up = new float[ndim];
    for( int i=0; i<ndim; i++ ) {
	low[i] = 0.0;
	up[i] = 1.0;
    }
    setBounds( low, up );
    delete low;
    delete up;
}

spaceSampler::spaceSampler( float step, int _ndim, float lowBound[], float upBound[] )
{
    init( step, _ndim );
    setBounds( lowBound, upBound );
}

spaceSampler::~spaceSampler()
{
    delete lowerBound;
    delete upperBound;
    delete currentSample;
    delete startPoint;
    delete targetPoint;
}

void
spaceSampler::init( float step, int _ndim )
{
    //
    //  do memory allocation
    //
    sampleSize = 1.0;
    setStepSize( step );

    ndim = _ndim;
    lowerBound = new float[ndim];
    upperBound = new float[ndim];
    currentSample = new float[ndim];
    startPoint = new float[ndim];
    targetPoint = new float[ndim];
}

void	
spaceSampler::setBounds( float lowBound[], float upBound[] )
{
    for( int i=0; i<ndim; i++ ) {
	lowerBound[i] = min( lowBound[i], upBound[i] );
	upperBound[i] = max( lowBound[i], upBound[i] );

	targetPoint[i] = lowerBound[i];
    }

    //  reset the sequence
    startNewSequence();
}

void	
spaceSampler::setStepSize( float size )
{
    if( size > 0 )
	sampleSize = size;
}


void	
spaceSampler::getSample( float sample[] )
{
    int	i;
    for( i=0; i<ndim; i++ ) {
	sample[i] = currentSample[i];
    }
#ifdef	TEST
    printf( "getSample:  { " );
    for( i=0; i<ndim; i++ ) {
	printf( "%g, ", sample[i] );
    }
    printf( "}\n" );
#endif	/* TEST */
}


void
spaceSampler::stepSample() 
{
    if( numSamplesLeft == 0 ) {			// run out of samples
	startNewSequence();
    }

    float	t = float(numRaySamples-numSamplesLeft)/numRaySamples;
    for( int i=0; i<ndim; i++ ) {
	currentSample[i] = t*(targetPoint[i]-startPoint[i]) + startPoint[i];
    }
    numSamplesLeft--;
}

void
spaceSampler::startNewSequence()
{
#ifdef	TEST
    printf( "startNewSequence\n" );
#endif	/* TEST */
    for( int i=0; i<ndim; i++ ) {
	startPoint[i] = targetPoint[i];
	currentSample[i] = targetPoint[i];
    }
    float	*randomPoint = new float[ndim];
    randomPointInInterval( lowerBound, upperBound, randomPoint );
    for(int i=0; i<ndim; i++ ) targetPoint[i] = randomPoint[i];
    clipRayToBox( startPoint, targetPoint );

    float	rayLength = getRayLength( startPoint, targetPoint );
    numRaySamples = int( ceil( rayLength / sampleSize ) );
    // assert( numRaySamples != 0 );	// somethin's not right
    if( numRaySamples == 0 ) numRaySamples = 1;
    numSamplesLeft = numRaySamples;

    delete randomPoint;			// used to catch assertion
}


void
spaceSampler::randomPointInInterval( float lower[], float upper[], 
					float result[] )
{
    for( int i=0; i<ndim; i++ ) {
	result[i] = drand48()*(upper[i]-lower[i]) + lower[i];
    }
}

//
//  parameterize vector from a to b, then intersect with each
//	boundary, and choose the one with the smallest positive 
//	parameter t:  R = t*(b-a) + a
//  Then redefine b for that value of t
//
void
spaceSampler::clipRayToBox( float a[], float b[] )
{
    int i;
    float tInt;
    float t = 3.4028234E+38F;		// CC chokes on FLT_MAX;
    for( i=0; i<ndim; i++ ) {
	tInt = (lowerBound[i] - a[i]) / (b[i] - a[i]);	// lower bound intersect
	if( tInt > 0.0 && tInt < t )
	    t = tInt;
	tInt = (upperBound[i] - a[i]) / (b[i] - a[i]);	// upper bound intersect
	if( tInt > 0.0 && tInt < t )
	    t = tInt;
    }

    for( i=0; i<ndim; i++ ) {
	b[i] = t*(b[i]-a[i]) + a[i];
	// assert( b[i] != a[i] );	// somethin's not right
    }
}

float
spaceSampler::getRayLength( float from[], float to[] )
{
    float	d = 0.0;
    for( int i=0; i<ndim; i++ ) {
	float	delta = to[i] - from[i];
	d += delta*delta;
    }
    return sqrt( d );
}


#ifdef	TEST
#include	<gl/gl.h>

int	
main( int argc, char *argv[] )
{
    float	step = .1;
    if( argc > 1 ) {
	step = atof( argv[1] );
    }

    spaceSampler sampler( step, 3 );

    foreground();
    prefposition( 0, 100, 800, 900 );
    winopen( "Space Sampler" );
    RGBmode();
    doublebuffer();
    gconfig();

    while( 1 ) {
	float	rgb[3];
	sampler.getSample( rgb );
	++sampler;

	unsigned long	rgba = (255 << 24)
	 		     | (int(255.0*rgb[2]) << 16)
			     | (int(255.0*rgb[1]) << 8)
			     |  int(255.0*rgb[0]);
	cpack( rgba );
	clear();
	swapbuffers();
    }
}

#endif	/* TEST */

