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


#include <math.h>
#include <gl.h>
#include <device.h>

#define PI2 	(2 * M_PI)

extern	float omega1;
extern	float omega2;
extern	float epsilon;

#ifdef	__cplusplus
extern "C" {
    void	makeMap( unsigned char *buf, int size, int maxCount );
    void	setEpsilon( float );
}
#endif



#if	0
#define SIZE 	(256)
#define MULT 	(2)
#define WINSIZE	(SIZE*MULT)

#define	MAPPOWER (8)
#define MAPSIZE (1<<MAPPOWER)

#define	MAXITER (SIZE*SIZE/1)	/* there's a chance of hitting every cell */
#define	INITITER 2000

extern	unsigned long	*dimBuf;
extern	unsigned char *buf;
extern	int count;

extern	long	mapWin;
extern	long	torusWin;


float computeD();
int drawit();
int drawpoint( int, int );
float frand( float, float );
int map( float, float, float*, float* );
int makeMap();
int random_function();
int reset_everything();
int setcolor( int );
void	setEpsilon( float );


/*  dimension buffer display routines */
void	setDimBuf( float, int, int, int );
void	drawDimBuf();

#endif
