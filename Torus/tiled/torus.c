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


#include <sys/types.h>
#include <malloc.h>
#include "math.h"
#include "gl.h"
#include "device.h"

#include "torusMap.h"



/* 
 *  program behavior constants
 */
int	tileFactor = 2;			/* tiling of torus space */
int	omegaSampleRate = 0;		/* sampling of omega w/in one torus */
int	limitHit = 0;

float	omegaZoom = 2;
float	omegaWindowSize = .001;

double	theta,psi;
int	iSample, jSample;		/* tile we are doing */

int	torusSize = 256;		/* size of torus in pixels */
int	winSize = 2*256;		/* size of window */

/*
 *  changing constants is modal, so here are the modes:
 */
enum	paramMode_t { 
		tiling, 		/* of tori */
		zooming,		/* making omega window larger/smaller */
		sampling		/* of omega, within one tile */
	} paramMode = tiling;

unsigned char *buf;			/* cell population buffer */
size_t	bufSize;			/* number of cells */
int count;				/* number of interations */

void
computeParameters()
{
    switch( paramMode ) {
	case tiling:
	    if( tileFactor < 1 ) tileFactor = 1;
	    torusSize = rint( ceil( winSize/(float)tileFactor ) );
	    winSize = torusSize*tileFactor;
	    prefsize( winSize, winSize );
	    winconstraints();
	    reset_everything();
	    break;
	case sampling:
	    if( omegaSampleRate < 0 ) omegaSampleRate = 0;
	    if( omegaSampleRate > 1 ) omegaSampleRate = 1;
	    reset_everything();
	    break;
	case zooming:
	    if( omegaZoom == 0 ) {
		omegaZoom = 2;
	    } else {
	        omegaWindowSize *= omegaZoom;
	    }
	    reset_everything();
	    break;
    }
}



void
printHelpInfo()
{
    puts( "" );
    puts( "t selects torus tiling factor parameter" );
    puts( "s selects omega sampling rate parameter" );
    puts( "z selects omega window zoom parameter" );
    puts( "up/down arrows increase/decrease current parameter" );
    puts( "h/H prints this message" );
    puts( "current parameter values:" );
    printf( "\tomega sampling rate = %d\n", omegaSampleRate );
    printf( "\tomega window zoom = %g\n", omegaWindowSize );
    printf( "\ttile factor = %d\n", tileFactor );
    printf( "\ttorus size = %d pixels\n", torusSize );
    printf( "\twindow size = %d pixels\n", winSize );
    printf( "\tthe current parameter is: " );
    switch( paramMode ) {
	case tiling:
	    printf( "torus tiling factor\n" );
	    break;
	case zooming:
    	    printf( "omega window zoom\n" );
	    break;
	case sampling:
    	    printf( "omega sampling rate\n" );
	    break;
    }
}


void
processInput( int block)
{
  short val;
  Device mdev[2];
  short mval[2];
  long int xorg,yorg;
  int	delta;

  mdev[0] = MOUSEX;
  mdev[1] = MOUSEY;

  while( block || qtest()) {
    long	dev;
    dev = qread (&val);
    if( ISBUTTON(dev) && val == 0 ) 
	continue;

    switch (dev) {
      case REDRAW:
	drawit();
	break;
      case LEFTMOUSE:  /* pick new omega (the translation factor) */
	computeD( buf );
	getdev (2, mdev, mval);
	getorigin (&xorg, &yorg);
	omega1 = (mval[0] - xorg) / (float) torusSize;
	omega2 = (mval[1] - yorg) / (float) torusSize;
	printf ("omega: %f %f\n", omega1, omega2);
	reset_everything();
	break;
      case MIDDLEMOUSE:  /* pick new epsilon (how much non-linearity) */
	computeD( buf );
	getdev (2, mdev, mval);
	getorigin (&xorg, &yorg);
	epsilon = (mval[0] - xorg) / (float) torusSize;
	printf ("epsilon: %f\n", epsilon);
	reset_everything();
	break;
      case RIGHTMOUSE:  /* choose another random non-linear function */
	computeD( buf );
	random_function();
	reset_everything();
	break;
      case TKEY:	/* select tile factor parameter */
	paramMode = tiling;
	printHelpInfo();
	break;
      case SKEY:	/* select omega sampling rate parameter */
	paramMode = sampling;
	printHelpInfo();
	break;
      case ZKEY:	/* select omega sampling rate parameter */
	paramMode = zooming;
	printHelpInfo();
	break;
      case HKEY:
	printHelpInfo();
	break;
      /*
       *  increment/decrement active parameter 
       */
      case UPARROWKEY:
      case DOWNARROWKEY:
	delta = (dev == UPARROWKEY) ? +1 : -1;
	switch( paramMode ) {
	    case tiling:
		tileFactor += delta;
		break;
	    case sampling:
		omegaSampleRate += delta;
		break;
	    case zooming:
		if( dev == UPARROWKEY ) omegaZoom = 2;
		if( dev == DOWNARROWKEY ) omegaZoom = .5;
		break;
	}
	computeParameters();
	break;
      case ESCKEY:
	exit( 0 );
	break;
      default:
	break;
    }
  }
}

main()
{
  int sampleNum;
  int x,y;
  unsigned char *cptr;

  printf ("\n");
  printf ("Left button sets omega.\n");
  printf ("Middle button sets epsilon, only left-right position matters.\n");
  printf ("Right button picks random function, mouse position ignored.\n");
  printf ("\n");

  bufSize = torusSize*torusSize;
  buf = (unsigned char *)malloc(bufSize*sizeof(unsigned char));
  prefsize(winSize,winSize);
  if( getenv( "DEBUG" ) )
	foreground();
  winopen("attractors");
  RGBmode();
  gconfig();
  winconstraints();
  reset_everything();

  qdevice (LEFTMOUSE);
  qdevice (MIDDLEMOUSE);
  qdevice (RIGHTMOUSE);
  qdevice (LKEY);
  qdevice (TKEY);
  qdevice (SKEY);
  qdevice (HKEY);
  qdevice (ZKEY);
  qdevice (ESCKEY);
  qdevice (DOWNARROWKEY);
  qdevice (UPARROWKEY);

  /* plot the successive iterates of an onto mapping of the torus */

  theta = psi = 0;  /* this initial point is arbitrary */

#if	0
  while (1) {
    map (theta, psi, &theta, &psi);

    x = theta * torusSize;
    y = psi * torusSize;

    count++;

    /* don't display the first few points because they may not begin */
    /* near the attractor */

    if (count > 2000 && x>=0 && x<torusSize && y>=0 && y<torusSize) {
      cptr = buf+((y*torusSize)+x);
      if (*cptr<255) {
	(*cptr)++;
	setcolor(*cptr);
	drawpoint(x,y);
      } else {
	limitHit = 1;
      }
    }

    if (count % 1000 == 0) {
        processInput( limitIterations && limitHit );
    }
  }    
#else
    while( 1 ) {
	if( omegaSampleRate == 0 )
	    sampleNum = 1;
	else
	    sampleNum = tileFactor*omegaSampleRate;
	for( jSample=0; jSample<sampleNum; jSample++ ) {
	    for( iSample=0; iSample<sampleNum; iSample++ ) {
		double	saveO1 = omega1;
		double	saveO2 = omega2;
		int	quit;

		omega1 += iSample*omegaWindowSize/(tileFactor*omegaSampleRate);
		omega2 += jSample*omegaWindowSize/(tileFactor*omegaSampleRate);

		theta = psi = 0;  /* this initial point is arbitrary */

		makeMap( buf, torusSize );
		drawSegment( iSample, jSample );

		omega1 = saveO1;
		omega2 = saveO2;
	    }
	}

	if (count % 1000 == 0) {
	    processInput( 1 );
        }
    }
#endif
}



/******************************************************************************
Clear the screen and zero the counts of all the screen pixels.
******************************************************************************/

reset_everything()
{
  if( torusSize*torusSize > bufSize ) {
    bufSize = torusSize*torusSize;
    buf = realloc( buf, bufSize*sizeof(unsigned char) );
  }
  bzero(buf,bufSize*sizeof(unsigned char));	
  cpack(0x000000);
  clear();
  count = 0;
  limitHit = 0;
    theta = psi = 0;
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
  ortho2(-0.5,winSize-0.5,-0.5,winSize-0.5);
  cpack(0x000000);
  clear();
  cptr = buf;
  for(y=0; y<torusSize; y++) {
    for(x=0; x<torusSize; x++) {
      setcolor(*cptr++);
      drawpoint(x,y);
    }
  }
}

drawpoint(x,y)
int x, y;
{
    int ix, iy;

    for(iy=0; iy<tileFactor; iy++)
  	for(ix=0; ix<tileFactor; ix++)
            pnt2i((ix*torusSize)+x,(iy*torusSize)+y);
}


drawSegment( int iseg, int jseg )
{
    int	ix, iy;

    for(iy=0; iy<tileFactor; iy++)
  	for(ix=0; ix<tileFactor; ix++)
            pnt2i((ix*torusSize)+ix,(iy*torusSize)+iy);
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
	int len = torusSize*torusSize;
	int i, count = 0;
	unsigned char	*p = buf;
	double	D;

	for( i=0; i<len; i++ ) {
		if( *p++ ) count++;
	}

	D = log(count)/log(torusSize);
	printf( "fractal Dimension = %.3g\n", D );
}
		


