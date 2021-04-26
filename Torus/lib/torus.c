#include <stdio.h>
#include <gl.h>
#include <math.h>


static int	numberOfIterations = 10000;

torus_var_init()
{
  static int initted = 0;
  if(!initted){
    /* init any important data structures */
    
    initted = 1;
  }
}


/*
 *  (default viewport mapping gives me pixel addressing)
 */
torus_init()
{
  doublebuffer();
  RGBmode();
}

torus_getviewport(str)
     char *str;
{
  Screencoord l, r, b, t;
  getviewport(&l, &r, &b, &t);
  sprintf(str, "%d %d %d %d\n", l, r, b, t);
}


torus_finish()
{
  finish();
}


torus_render()
{
    double theta, psi;
    int x, y;
    int	i;
    Screencoord l, r, b, t;
    int	size;

    cpack( 0x0 );
    clear();

    /*  get min viewport size */
    getviewport(&l, &r, &b, &t);
    size = r - l + 1;
    if( t - b + 1 < size ) size = t - b + 1;

    cpack( 0xffffffff );
    theta = psi = 0;  /* this initial point is arbitrary */
    for( i=0; i<numberOfIterations; i++ ) {
	map (theta, psi, &theta, &psi);

	x = theta * size;
	y = psi * size;
	pnt2i( x, y );
    }

    swapbuffers();
    gflush();
}

torusSet(pname, val, set)
     char *pname, *val;
     int set;
{
    extern double omega1;
    extern double omega2;
    extern double epsilon;

  if(strcmp(pname, "omega1") == 0){
    if(set)
      omega1 = atof(val);
    else
      sprintf(val, "%d", omega1);
  } else if(strcmp(pname, "omega2") == 0){
    if(set)
      omega2 = atof(val);
    else
      sprintf(val, "%d", omega2);
  } else if(strcmp(pname, "epsilon") == 0){
    if(set)
      epsilon = atof(val);
    else
      sprintf(val, "%d", epsilon);
  } else
    return(1);

  return(0);
}


/*  START OF TORUS SPECIFIC CODE */

#include "math.h"

#define PI2 	(2 * 3.14159265358979323)

/* constants for function P */

#define COEFFS 4

double a1[COEFFS] = { -0.26813663648754, -0.91067559396390,
		       0.31172026382793, -0.04003977835470 };

double a2[COEFFS] = { 0.08818611671542, -0.56502889980448,
		      0.16299548727086, -0.80398881978155 };

double b1[COEFFS] = { 0.98546084298505, 0.50446045609351,
		      0.94707472523078, 0.23350105508507 };

double b2[COEFFS] = { 0.99030722865609, 0.33630697012268,
		      0.29804921230971, 0.15506467277737 };

double r[COEFFS] = {1, 0, 1, 1};
double s[COEFFS] = {0, 1, 1, -1};

double omega1 = 0.48566516831488;
double omega2 = 0.90519373301868;
double epsilon = 0.5;

double originalOmega1 = 0.48566516831488;
double originalOmega2 = 0.90519373301868;

/******************************************************************************
Mapping of a point (theta,psi) from the torus onto the torus.

F(theta,psi) = (theta + omega1 + epsilon * P1, psi + omega2 + epsilon * P2)
where P1 and P2 are "random" functions of theta and psi.  The system becomes
less predictable as epsilon increases.
******************************************************************************/

map(theta,psi,theta2,psi2)
  double theta,psi;	/* input */
  double *theta2,*psi2;	/* output */
{
  int i;
  double t,p;
  double p1,p2;

  p1 = p2 = 0;
  for (i = 0; i < COEFFS; i++) {
    p1 += a1[i] * sin (PI2 * (r[i] * theta + s[i] * psi + b1[i]));
    p2 += a2[i] * sin (PI2 * (r[i] * theta + s[i] * psi + b2[i]));
  }

  t = theta + omega1 + epsilon * p1 / PI2;
  p = psi   + omega2 + epsilon * p2 / PI2;

  /* compute mod 1 of the resulting values to keep them on the torus */

  t = t - floor (t);
  if (t < 0)
    t += 1;

  p = p - floor (p);
  if (p < 0)
    p += 1;

  *theta2 = t;
  *psi2 = p;
}


#if	0

/* ================= */

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


#include "gl.h"
#include "device.h"

#define SIZE 	(300)
#define MULT 	(2)
#define WINSIZE	(SIZE*MULT)

unsigned char *buf;
int count;

#define CONSC	(0.001)

main()
{
  int x,y;
  unsigned char *cptr;
  double theta,psi;
  short val;
  short mval[2];
  Device mdev[2];
  long int xorg,yorg;

  printf ("\n");
  printf ("Left button sets omega.\n");
  printf ("Middle button sets epsilon, only left-right position matters.\n");
  printf ("Right button picks random function, mouse position ignored.\n");
  printf ("\n");

  buf = (unsigned char *)malloc(SIZE*SIZE*sizeof(unsigned char));
  prefsize(WINSIZE,WINSIZE);
  if( getenv( "DEBUG" ) )
	foreground();
  winopen("attractors");
  RGBmode();
  gconfig();
  reset_everything();

  qdevice (LEFTMOUSE);
  qdevice (MIDDLEMOUSE);
  qdevice (RIGHTMOUSE);
  mdev[0] = MOUSEX;
  mdev[1] = MOUSEY;

  /* plot the successive iterates of an onto mapping of the torus */

  theta = psi = 0;  /* this initial point is arbitrary */

  while (1) {

    map (theta, psi, &theta, &psi);

    x = theta * SIZE;
    y = psi * SIZE;

    count++;

    /* don't display the first few points because they may not begin */
    /* near the attractor */

    if (count > 2000 && x>=0 && x<SIZE && y>=0 && y<SIZE) {
      cptr = buf+((y*SIZE)+x);
      if (*cptr<255) {
	(*cptr)++;
	setcolor(*cptr);
	drawpoint(x,y);
      }
    }

    if (count % 1000 == 0) {
      while(qtest()) {
	switch (qread (&val)) {
	  case REDRAW:
	    drawit();
	    break;
	  case LEFTMOUSE:  /* pick new omega (the translation factor) */
	    if (val == 0)
	      break;
	    getdev (2, mdev, mval);
	    getorigin (&xorg, &yorg);
	    omega1 = (mval[0] - xorg) / (float) SIZE;
	    omega2 = (mval[1] - yorg) / (float) SIZE;
	   /* omega1 = originalOmega1 + CONSC*((-WINSIZE/2 + mval[0] - xorg) / (float) WINSIZE);
	    omega2 = originalOmega2 + CONSC*((-WINSIZE/2 + mval[1] - yorg) / (float) WINSIZE);
*/
	    printf ("omega: %f %f\n", omega1, omega2);
	    theta = psi = 0;
            computeD( buf );
	    reset_everything();
	    break;
	  case MIDDLEMOUSE:  /* pick new epsilon (how much non-linearity) */
	    if (val == 0)
	      break;
	    getdev (2, mdev, mval);
	    getorigin (&xorg, &yorg);
	    epsilon = (mval[0] - xorg) / (float) SIZE;
	    printf ("epsilon: %f\n", epsilon);
	    theta = psi = 0;
            computeD( buf );
	    reset_everything();
	    break;
	  case RIGHTMOUSE:  /* choose another random non-linear function */
	    if (val == 0)
	      break;
	    random_function();
            computeD( buf );
	    reset_everything();
	    break;
	  default:
	    break;
	}
      }
    }
  }    
}


/******************************************************************************
Pick new random coefficients for the functions P1 and P2.  See map().
******************************************************************************/

random_function()
{
  int i;
  double frand();

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
Clear the screen and zero the counts of all the screen pixels.
******************************************************************************/

reset_everything()
{
  bzero(buf,SIZE*SIZE*sizeof(unsigned char));
  cpack(0x000000);
  clear();
  count = 0;
}


/******************************************************************************
Set current color to a shade of gray based on given value.
******************************************************************************/

setcolor(c)
  int c;
{
  if(c == 0)
    cpack(0x000000);
  else {
    c =  20+c * 4;
    if(c>255)
      c = 255;
    cpack(0x010101*c);
  }
}


/******************************************************************************
Redraw the screen.
******************************************************************************/

drawit()
{
  int x, y;
  unsigned char *cptr;

  reshapeviewport();
  ortho2(-0.5,WINSIZE-0.5,-0.5,WINSIZE-0.5);
  cpack(0x000000);
  clear();
  cptr = buf;
  for(y=0; y<SIZE; y++) {
    for(x=0; x<SIZE; x++) {
      setcolor(*cptr++);
      drawpoint(x,y);
    }
  }
}

drawpoint(x,y)
int x, y;
{
    int ix, iy;

    for(iy=0; iy<MULT; iy++)
  	for(ix=0; ix<MULT; ix++)
            pnt2i((ix*SIZE)+x,(iy*SIZE)+y);
}

/******************************************************************************
Pick a random number between min and max.
******************************************************************************/

double frand(min, max)
  double min,max;
{
#define  RAND_RANGE  100000    /* resolution of random numbers */
  long random();
  int result;

  result = random() % RAND_RANGE;
  return (min + (max - min) * (result / (double) RAND_RANGE));
}


/*  
 *  compute fractal dimension
 *  	this may not be correct if size != 2^N
 */
computeD()
{
	int len = SIZE*SIZE;
	int i, count = 0;
	unsigned char	*p = buf;
	double	D;

	for( i=0; i<len; i++ ) {
		if( *p++ ) count++;
	}

	D = log(count)/log(SIZE);
	printf( "fractal Dimension = %.3g\n", D );
}
		


#endif
