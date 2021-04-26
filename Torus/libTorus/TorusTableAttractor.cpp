//
//  define an ADT that implements the torus attractor mapping
//

#include <TorusTableAttractor.h>
#include "math.h"
#include <stdio.h>

#define PI2 	(2 * 3.14159265358979323)


TorusTableAttractor::TorusTableAttractor( int _xCellRes, int _yCellRes )
{
    xCellRes = _xCellRes;
    yCellRes = _yCellRes;
    p1Array = NULL;
    p2Array = NULL;
    resetParameters();
}

TorusTableAttractor::~TorusTableAttractor() 
{
    delete p1Array;
    delete p2Array;
}


void	
TorusTableAttractor::computeP1P2( double theta, double psi, 
		  double *p1, double *p2 )
{
#define	MOD_TP(x)					\
    if( x < 0.0 || x >= 1.0 ) {				\
	x -= floor( x );				\
	if( x < 0.0 )					\
	    x += 1.0;					\
    }

    MOD_TP(theta);
    MOD_TP(psi);
#undef	MOD_TP

    *p1 = p1Array[int(theta*xCellRes)+xCellRes*int(psi*yCellRes)];
    *p2 = p2Array[int(theta*xCellRes)+xCellRes*int(psi*yCellRes)];
}


void
TorusTableAttractor::allocateP1P2Arrays()
{
    if( p1Array == NULL || p2Array == NULL ) {
	p1Array = new float[xCellRes*yCellRes];
	p2Array = new float[xCellRes*yCellRes];
    }
}


void
TorusTableAttractor::computeP1P2Arrays()
{
    allocateP1P2Arrays();
    for( int y=0; y<yCellRes; y++ ) {
	float	psi = float(y + 0.5)/yCellRes;
	for( int x=0; x<xCellRes; x++ ) {
	    float	theta = float(x + 0.5)/xCellRes;
	    double	p1;
	    double	p2;
	    TorusAttractor::computeP1P2( theta, psi, &p1, &p2 );
	    p1Array[int(theta*xCellRes)+xCellRes*int(psi*yCellRes)] = p1;
	    p2Array[int(theta*xCellRes)+xCellRes*int(psi*yCellRes)] = p2;
	}
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
TorusTableAttractor::computeRange( const Interval &, const Interval &, 
			const Interval &, Interval &theta )
{
    theta.setMin( 0.0 );
    theta.setMax( 1.0 );
}




// resets omegas, epsilon and arrays
void	
TorusTableAttractor::randomizeArrays()
{
    TorusAttractor::randomizeArrays();
    computeP1P2Arrays();
}


// resets omegas, epsilon and arrays
void	
TorusTableAttractor::resetParameters()
{
    TorusAttractor::resetParameters();
    computeP1P2Arrays();
}





