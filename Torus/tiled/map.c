#include	"torus.h"
#include	<strings.h>


/* constants for function P */

#define COEFFS 4

float a1[COEFFS] = { -0.26813663648754, -0.91067559396390,
		       0.31172026382793, -0.04003977835470 };

float a2[COEFFS] = { 0.08818611671542, -0.56502889980448,
		      0.16299548727086, -0.80398881978155 };

float b1[COEFFS] = { 0.98546084298505, 0.50446045609351,
		      0.94707472523078, 0.23350105508507 };

float b2[COEFFS] = { 0.99030722865609, 0.33630697012268,
		      0.29804921230971, 0.15506467277737 };

float r[COEFFS] = {1, 0, 1, 1};
float s[COEFFS] = {0, 1, 1, -1};

float omega1 = 0.48566516831488;
float omega2 = 0.90519373301868;
float epsilon = 0.5;
float e_div_PI2;

float orgomega1 = 0.48566516831488;
float orgomega2 = 0.90519373301868;
#define CONSC	(0.001)

/*
 *  set epsilon and calculate any needed coefficients
 */
void
setEpsilon( float e )
{
	epsilon = e;
	e_div_PI2 = e / PI2;
}

/******************************************************************************
Pick a random number between min and max.
******************************************************************************/

double frand( double min, double max )
{
#define  RAND_RANGE  100000    /* resolution of random numbers */
  long random();
  int result;

  result = random() % RAND_RANGE;
  return (min + (max - min) * (result / (double) RAND_RANGE));
}

/******************************************************************************
Pick new random coefficients for the functions P1 and P2.  See map().
******************************************************************************/

void
random_function()
{
  int i;

  /* a1 and a2 coefficients could actually be larger since they are */
  /* used as amplitudes of sine waves in computing P1 and P2 */

  /* the values of b1 and b2 are effectively mapped into [0,1] by */
  /* the multiplication by 2*pi in computing P1 and P2, so there */
  /* is nothing to be gained by expanding their range */

  for (i = 0; i < COEFFS; i++) {
    a1[i] = frand (-1.0, 1.0);
    a2[i] = frand (-1.0, 1.0);
    b1[i] = frand (0.0, 1.0);
    b2[i] = frand (0.0, 1.0);
  }
}


/******************************************************************************
Mapping of a point (theta,psi) from the torus onto the torus.

F(theta,psi) = (theta + omega1 + epsilon * P1, psi + omega2 + epsilon * P2)
where P1 and P2 are "random" functions of theta and psi.  The system becomes
less predictable as epsilon increases.
******************************************************************************/

void
map(float theta,float psi,float *theta2,float *psi2)
  /* float theta,psi;	input */
  /* float *theta2,*psi2;	output */
{
  int i;
  float t,p;
  register float p1,p2;

  p1 = p2 = 0;
  for (i = 0; i < COEFFS; i++) {
    register float	rT_sP = r[i] * theta + s[i] * psi;
    p1 += a1[i] * sin (PI2 * (rT_sP + b1[i]));
    p2 += a2[i] * sin (PI2 * (rT_sP + b2[i]));
  }

  t = theta + omega1 + e_div_PI2 * p1;
  p = psi   + omega2 + e_div_PI2 * p2;

  /* compute mod 1 of the resulting values to keep them on the torus */

  t = t - floorf (t);
  if (t < 0)
    t += 1;

  p = p - floorf (p);
  if (p < 0)
    p += 1;

  *theta2 = t;
  *psi2 = p;
}




void
makeMap( unsigned char *buf, int size, int maxCount )
{
    float theta,psi;
    int	x, y;
    unsigned char *cptr;
    int	count = 0;

    /* pick arbitrary initial point */
    theta = psi = 0;  /* this initial point is arbitrary */

    bzero( buf, size*size );

    while( count < 2000 ) {
	map( theta, psi, &theta, &psi );
	count++;
    }

    while( 1 ) {
	map( theta, psi, &theta, &psi );
	x = theta * size;
	y = psi * size;
	cptr = buf+((y*size)+x);
	if( *cptr == maxCount ) {
	    return;
	}
	(*cptr)++;
    }
}

