//
//  Separate evaluation of Torus from the drawing:
//
//	This class does nothing but evaluation of the 2D (and 3D?) torus
//
#define _USE_MATH_DEFINES

#include	<iostream>
#include	<math.h>
#include	<stdlib.h>

#include	"TorusEvaluator.h"

#define	PI2 (2*M_PI)

using namespace std;

// defaults
// two dimensions
#define	NUM_COEFFS_2	4
float _defA1_2[NUM_COEFFS_2] = { -0.26813663648754f, -0.91067559396390f,
		       0.31172026382793f, -0.04003977835470f };

float _defA2_2[NUM_COEFFS_2] = { 0.08818611671542f, -0.56502889980448f,
		      0.16299548727086f, -0.80398881978155f };

float _defB1_2[NUM_COEFFS_2] = { 0.98546084298505f, 0.50446045609351f,
		      0.94707472523078f, 0.23350105508507f };

float _defB2_2[NUM_COEFFS_2] = { 0.99030722865609f, 0.33630697012268f,
		      0.29804921230971f, 0.15506467277737f };

float _defA3_2[NUM_COEFFS_2];
float _defB3_2[NUM_COEFFS_2];

float _defR_2[NUM_COEFFS_2] = { 1.0f, 0.0f, 1.0f, 1.0f };
float _defS_2[NUM_COEFFS_2] = { 0.0f, 1.0f, 1.0f, -1.0f };
float _defT_2[NUM_COEFFS_2];

float _defOmega2[2] = { 0.48566516831488f, 0.90519373301868f };

// three dimensions
float _defR_3[] = { 1.0f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, -1.0f,  1.0f,  1.0f,  1.0f, -1.0f, -1.0f };
float _defS_3[] = { 0.0f,  1.0f,  0.0f,  1.0f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,  1.0f, -1.0f,  1.0f, -1.0f,  1.0f, -1.0f };
float _defT_3[] = { 0.0f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f, -1.0f,  1.0f, -1.0f,  1.0f,  1.0f,  1.0f, -1.0f, -1.0f, -1.0f,  1.0f };

#define	NUM_COEFFS_3	(sizeof(_defR_3)/sizeof(float))

float _defA1_3[NUM_COEFFS_3] = { -0.26813663648754f, -0.91067559396390f,
		       0.31172026382793f, -0.04003977835470f };

float _defA2_3[NUM_COEFFS_3] = { 0.08818611671542f, -0.56502889980448f,
		      0.16299548727086f, -0.80398881978155f };

float _defB1_3[NUM_COEFFS_3] = { 0.98546084298505f, 0.50446045609351f,
		      0.94707472523078f, 0.23350105508507f };

float _defB2_3[NUM_COEFFS_3] = { 0.99030722865609f, 0.33630697012268f,
		      0.29804921230971f, 0.15506467277737f };

float _defA3_3[NUM_COEFFS_3];
float _defB3_3[NUM_COEFFS_3];

float _defOmega3[3] = { 0.48566516831488f, 0.90519373301868f };

TorusEvaluator::TorusEvaluator( int dimension )
	: rng()
	, uni_01(0,1)
	, rand(rng, uni_01)
{
    if( dimension < 2 || dimension > 3 ) {
	cerr << "bad dimension: " << dimension << ", using 2\n";
	dimension = 2;
    }

    _dim = dimension;
    if( _dim == 2 ) {
	_numCoeffs = NUM_COEFFS_2;
    } else {
	_numCoeffs = NUM_COEFFS_3;
    } 

    _omega = new float[_dim];
    _r = new float[_numCoeffs];
    _s = new float[_numCoeffs];
    _t = new float[_numCoeffs];
    _a1 = new float[_numCoeffs];
    _b1 = new float[_numCoeffs];
    _a2 = new float[_numCoeffs];
    _b2 = new float[_numCoeffs];
    _a3 = new float[_numCoeffs];	// allocate them anyway, its cheap
    _b3 = new float[_numCoeffs];

    init();
}

// more for subclasses than anyone
TorusEvaluator::~TorusEvaluator()
{
    delete _omega;
    delete _r;
    delete _s;
    delete _t;
    delete _a1;
    delete _b1;
    delete _a2;
    delete _b2;
    delete _a3;
    delete _b3;
}

//
//  standard initial values
//
void	
TorusEvaluator::init()
{
    _epsilon = 0.5;
    int	n = _numCoeffs*sizeof(float);
    memcpy( _omega, _dim == 2 ? _defOmega2 : _defOmega3, _dim*sizeof(float) );
    memcpy( _r, _dim == 2 ? _defR_2 : _defR_3, n );
    memcpy( _s, _dim == 2 ? _defS_2 : _defS_3, n );
    memcpy( _t, _dim == 2 ? _defT_2 : _defT_3, n );
    memcpy( _a1, _dim == 2 ? _defA1_2 : _defA1_3, n );
    memcpy( _b1, _dim == 2 ? _defB1_2 : _defB1_3, n );
    memcpy( _a2, _dim == 2 ? _defA2_2 : _defA2_3, n );
    memcpy( _b2, _dim == 2 ? _defB2_2 : _defB2_3, n );
    memcpy( _a3, _dim == 2 ? _defA3_2 : _defA3_3, n );	// its not really overrun
    memcpy( _b3, _dim == 2 ? _defB3_2 : _defB3_3, n );
}


// evaluate one point in two dimensions
void	
TorusEvaluator::eval2( float pout[], float pin[] )
{
  int i;
  float p0, p1;

  p0 = p1 = 0.0;
  for (i = 0; i < NUM_COEFFS_2; i++) {
    p0 += _a1[i] * sinf (PI2 * (_r[i]*pin[0] + _s[i]*pin[1] + _b1[i]));
    p1 += _a2[i] * sinf (PI2 * (_r[i]*pin[0] + _s[i]*pin[1] + _b2[i]));
  }

  p0 = pin[0] + _omega[0] + _epsilon * p0 / PI2;
  p1 = pin[1] + _omega[1] + _epsilon * p1 / PI2;

  /* compute mod 1 of the resulting values to keep them on the torus */

  p0 = p0 - floor (p0);
  if (p0 < 0)
    p0 += 1;

  p1 = p1 - floor (p1);
  if (p1 < 0)
    p1 += 1;

  pout[0] = p0;
  pout[1] = p1;
}

// evaluate one point in three dimensions
void	
TorusEvaluator::eval3( float pout[], float pin[] )
{
  int i;
  float p0, p1, p2;

  p0 = p1 = p2 = 0.0;
  for (i = 0; i < NUM_COEFFS_3; i++) {
    p0 += _a1[i] * sinf (PI2 * (_r[i]*pin[0] + _s[i]*pin[1] + _t[i]*pin[2] + _b1[i]));
    p1 += _a2[i] * sinf (PI2 * (_r[i]*pin[0] + _s[i]*pin[1] + _t[i]*pin[2] + _b2[i]));
    p2 += _a3[i] * sinf (PI2 * (_r[i]*pin[0] + _s[i]*pin[1] + _t[i]*pin[2] + _b3[i]));
  }

  p0 = pin[0] + _omega[0] + _epsilon * p0 / PI2;
  p1 = pin[1] + _omega[1] + _epsilon * p1 / PI2;
  p2 = pin[2] + _omega[2] + _epsilon * p2 / PI2;

  /* compute mod 1 of the resulting values to keep them on the torus */

  p0 = p0 - floor (p0);
  if (p0 < 0)
    p0 += 1;

  p1 = p1 - floor (p1);
  if (p1 < 0)
    p1 += 1;

  p2 = p2 - floor (p2);
  if (p2 < 0)
    p2 += 1;

  pout[0] = p0;
  pout[1] = p1;
  pout[2] = p2;
}

void	
TorusEvaluator::eval( float pout[], float pin[] )
{
    if( _dim == 2 ) {
	eval2( pout, pin );
    } else {
	eval3( pout, pin );
    }
}

void	
TorusEvaluator::eval( int num, float *pout, float *pin )
{
    if( 2 == _dim ) {
	for( ; num>=0; num--, pin += _dim, pout += _dim ) {
	    eval2( pout, pin );
	}
    } else {
	for( ; num>=0; num--, pin += _dim, pout += _dim ) {
	    eval3( pout, pin );
	}
    }
}

// OK, expose some of the internals
void	
TorusEvaluator::setOmega( float o[] )
{
	_omega[0] = o[0];
	_omega[1] = o[1];
	if(3 == _dim)
		{
		_omega[2] = o[2];
		}
}

void	
TorusEvaluator::setEpsilon( float e )
{
}

void	
TorusEvaluator::setA1( float a[] )
{
}

void	
TorusEvaluator::setB1( float b[] )
{
}


// randomize A or B
void	
TorusEvaluator::randomizeA()
{
    for( int i=0; i<_numCoeffs; i++ ) {
	// random numbers on range [-1.0,1.0]
	_a1[i] = 2*drand48() - 1.0;
	_a2[i] = 2*drand48() - 1.0;
	_a3[i] = 2*drand48() - 1.0;
    }
}

void	
TorusEvaluator::randomizeB()
{
    for( int i=0; i<_numCoeffs; i++ ) {
	// random numbers on range [0.0,1.0]
	_b1[i] = drand48();
	_b2[i] = drand48();
	_b3[i] = drand48();
    }
}



