//
//  define an ADT that implements the torus attractor mapping
//

#define _USE_MATH_DEFINES

#include <TorusAttractor.h>
#include <math.h>
#include <stdio.h>

#define PI2 	(2 * M_PI)

double TorusAttractor::defaultA1[NUM_COEFFS] = { 
			-0.26813663648754, -0.91067559396390,
		       	0.31172026382793, -0.04003977835470 
		    };

double TorusAttractor::defaultA2[NUM_COEFFS] = { 
			0.08818611671542, -0.56502889980448,
		      	0.16299548727086, -0.80398881978155 
		    };

double TorusAttractor::defaultB1[NUM_COEFFS] = { 
			0.98546084298505, 0.50446045609351,
		      	0.94707472523078, 0.23350105508507 
		    };

double TorusAttractor::defaultB2[NUM_COEFFS] = { 
			0.99030722865609, 0.33630697012268,
		      	0.29804921230971, 0.15506467277737 
		    };

double TorusAttractor::defaultR[NUM_COEFFS] = {1, 0, 1, 1};
double TorusAttractor::defaultS[NUM_COEFFS] = {0, 1, 1, -1};

double TorusAttractor::defaultOmega1 = 0.48566516831488;
double TorusAttractor::defaultOmega2 = 0.90519373301868;
double TorusAttractor::defaultEpsilon = 0.5;

TorusAttractor::TorusAttractor()
	: rng()
	, uni_01(0,1)
	, rand(rng, uni_01)
{
    wrapMapping = 1;
    resetParameters();
}

TorusAttractor::~TorusAttractor() {}


/******************************************************************************
Mapping of a point (theta,psi) from the torus onto the torus.

F(theta,psi) = (theta + omega1 + epsilon * P1, psi + omega2 + epsilon * P2)
where P1 and P2 are "random" functions of theta and psi.  The system becomes
less predictable as epsilon increases.
******************************************************************************/
void	
TorusAttractor::mapPoint( double theta, double psi, 
		  double *newTheta, double *newPsi )
{
  double t,p;
  double p1,p2;

  computeP1P2( theta, psi, &p1, &p2 );

  t = theta + omega1 + epsilon * p1 / PI2;
  p = psi   + omega2 + epsilon * p2 / PI2;

  /* compute mod 1 of the resulting values to keep them on the torus */

  if( wrapMapping ) {
      t = t - floor (t);
      if (t < 0)
	t += 1;

      p = p - floor (p);
      if (p < 0)
	p += 1;
  }

  *newTheta = t;
  *newPsi = p;
}


void
TorusAttractor::computeP1P2( double theta, double psi, double *p1, double *p2 )
{
    *p1 = 0.0;
    *p2 = 0.0;
    for ( int i = 0; i < NUM_COEFFS; i++) {
	*p1 += a1[i] * sin (PI2 * (r[i] * theta + s[i] * psi + b1[i]));
	*p2 += a2[i] * sin (PI2 * (r[i] * theta + s[i] * psi + b2[i]));
    }
}


//
//  this works for theta or psi
    //
    //  the equations we are computing the range for are:
    //	  t = theta + omega1 + epsilon * p1 / PI2;
    //	  p = psi   + omega2 + epsilon * p2 / PI2;
    //
    //  assume that theta has its input range set;
    //
//
void
TorusAttractor::computeRange( const Interval &omega, const Interval &eps, 
			const Interval &param, Interval &theta )
{
    Interval	x = eps;
    x *= param;
    x /= PI2;
    x += omega;
    theta += x;
}

//
//  
//
void
TorusAttractor::computeRanges( int N, const Interval &om1, const Interval &om2,
		    const Interval &eps, Interval &theta, Interval &psi )
{
    //
    //  first compute the range of the P1 and P2 variables.  
    //	   Assume that the range of the sin() term is [-1,+1]
    //	XXX this is an OK assumption, but the computation of the max 
    //	as the sum of the max amplitudes is flawed.  In one dimension,
    //	it is equivalent to saying that 
    //	min(a*sin(w*t+b) + c*sin(v*t+d)) = min(a*sin(w*t+b)) + min(c*sin(v*t+d))
    //					= -a + -b = -(a+b)
    //  which is too conservative
    //
    Interval	sinRange( -1.0, +1.0 );
    Interval	p1( 0.0, 0.0 );		// we add intervals that include 0
    Interval	p2( 0.0, 0.0 );		// so this is OK
    
    for( int i=0; i<NUM_COEFFS; i++ ) {
	Interval	t;
	t = sinRange;
	t *= a1[i];
	p1 += t;

	t = sinRange;
	t *= a2[i];
	p2 += t;
    }

    for( i=0; i<N; i++ ) {
	computeRange( om1, eps, p1, theta );
	computeRange( om2, eps, p2, psi );
    }
}

void	
TorusAttractor::setOmega1( double newOmega1 )
{
    omega1 = newOmega1;
}

void	
TorusAttractor::setOmega2( double newOmega2 )
{
    omega2 = newOmega2;
}

void	
TorusAttractor::setEpsilon( double newEpsilon )
{
    epsilon = newEpsilon;
}

/******************************************************************************
Pick new random coefficients for the functions P1 and P2.  See map().
******************************************************************************/
void
TorusAttractor::setArrays( float A1[], float A2[], float B1[], float B2[] )
{
    for( int i=0; i<NUM_COEFFS; i++ ) {
	a1[i] = A1[i];
	a2[i] = A2[i];
	b1[i] = B1[i];
	b2[i] = B2[i];
    }
}


void	
TorusAttractor::randomizeArrays()
{
  int i;

  /* a1 and a2 coefficients could actually be larger since they are */
  /* used as amplitudes of sine waves in computing P1 and P2 */

  /* the values of b1 and b2 are effectively mapped into [0,1] by */
  /* the multiplication by 2*pi in computing P1 and P2, so there */
  /* is nothing to be gained by expanding their range */

  for (i = 0; i < NUM_COEFFS; i++) {
    a1[i] = frand (-1.0, 1.0);
    a2[i] = frand (-1.0, 1.0);
    b1[i] = frand (0.0, 1.0);
    b2[i] = frand (0.0, 1.0);
  }
}



// resets omegas, epsilon and arrays
void	
TorusAttractor::resetParameters()
{

    omega1 = defaultOmega1;
    omega2 = defaultOmega2;
    epsilon = defaultEpsilon;

    for( int i=0; i<NUM_COEFFS; i++ ) {
	a1[i] = defaultA1[i];
	a2[i] = defaultA2[i];
	b1[i] = defaultB1[i];
	b2[i] = defaultB2[i];
	r[i] = defaultR[i];
	s[i] = defaultS[i];
    }
}




/******************************************************************************
Pick a random number between min and max.
******************************************************************************/
double 
TorusAttractor::frand(double min, double max)
{
  return min + (max - min)*rand();
}




