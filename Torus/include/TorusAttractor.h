#ifndef	_TORUSATTRACTOR_H__
#define	_TORUSATTRACTOR_H__
//
//  define an ADT that implements the torus attractor mapping
//

#include	<interval.h>

#include	<boost/random/uniform_real.hpp>
#include	<boost/random/uniform_01.hpp>
#include	<boost/random/linear_congruential.hpp>
#include	<boost/random/variate_generator.hpp>

#define	NUM_COEFFS	4

class	TorusAttractor {
public:
    TorusAttractor();
    ~TorusAttractor();

    void	mapPoint( double theta, double psi, 
				  double *newTheta, double *newPsi );
    
    void	wrapMap() { wrapMapping = 1; }
    void	noWrapMap() { wrapMapping = 0; }
    
    void	setOmega1( double newOmega1 );
    void	setOmega2( double newOmega2 );
    void	setEpsilon( double newEpsilon );

    virtual	void	randomizeArrays();
    void	setArrays( float A1[], float A2[], float B1[], float B2[] );

    virtual	void	resetParameters();// resets omegas, epsilon and arrays
    void	computeRanges( int N, const Interval &om1, 
				const Interval &om2,
				const Interval &eps, 
				Interval &theta, Interval &psi );

protected:
    double	omega1, omega2;		// attractor shape controls
    double	epsilon;		// 'chaoticness' parameter

    double	a1[NUM_COEFFS];		// arrays used in mapping
    double	a2[NUM_COEFFS];
    double	b1[NUM_COEFFS];
    double	b2[NUM_COEFFS];
    double	r[NUM_COEFFS];
    double	s[NUM_COEFFS];

    //  default values for all of the above
    static	double	defaultOmega1, defaultOmega2;
    static	double	defaultEpsilon;	

    static	double	defaultA1[NUM_COEFFS];
    static	double	defaultA2[NUM_COEFFS];
    static	double	defaultB1[NUM_COEFFS];
    static	double	defaultB2[NUM_COEFFS];
    static	double	defaultR[NUM_COEFFS];
    static	double	defaultS[NUM_COEFFS];

    float	*p1Array, *p2Array;
    int		xCellRes, yCellRes;
    void	allocateP1P2Arrays();
    void	computeP1P2Arrays();

    int		wrapMapping;		// wrap points?

    virtual	void	computeP1P2( double theta, double psi, 
				double *p1, double *p2 );
    virtual	void	computeRange( const Interval &omega, 
				const Interval &eps, 
				const Interval &param, Interval &theta );
    double	frand( double min, double max );

	// boost random number generator as a replacement for drand48
	boost::rand48 rng;
	boost::uniform_real<> uni_01;
	boost::variate_generator<boost::rand48&, boost::uniform_real<> > rand;
	double drand48() { return rand(); }
};

#endif	/* _TORUSATTRACTOR_H__ */
