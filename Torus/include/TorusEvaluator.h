//
//  Separate evaluation of Torus from the drawing:
//
//	This class does nothing but evaluation of the 2D (and 3D?) torus
//

#include	<boost/random/uniform_real.hpp>
#include	<boost/random/uniform_01.hpp>
#include	<boost/random/linear_congruential.hpp>
#include	<boost/random/variate_generator.hpp>


class	TorusEvaluator {
public:
    TorusEvaluator( int dimension = 2 );
    virtual	~TorusEvaluator();	// more for subclasses than anyone

    // evaluate one or many points
    void	eval( float pout[], float pin[] );
    void	eval( int num, float pout[], float pin[] );

    // OK, expose some of the internals
    int		getDim()	{ return _dim; }
    int		getNumCoeffs()	{ return _numCoeffs; }
    void	setOmega( float o[] );
    void	setEpsilon( float e );
    void	setA1( float a[] );
    void	setB1( float b[] );
    void	setA2( float a[] );
    void	setB2( float b[] );
    void	setA3( float a[] );
    void	setB3( float b[] );

    // randomize A or B
    void	randomizeA();
    void	randomizeB();

    virtual void	init();			// return to the default values

protected:
    void	eval2( float pout[], float pin[] );
    void	eval3( float pout[], float pin[] );

    int		_dim;
    int		_numCoeffs;
    float	_epsilon;
    float	*_omega;
    float	*_a1, *_b1;
    float	*_a2, *_b2;
    float	*_a3, *_b3;
    float	*_r, *_s, *_t;

	// boost random number generator as a replacement for drand48
	boost::rand48 rng;
	boost::uniform_real<> uni_01;
	boost::variate_generator<boost::rand48&, boost::uniform_real<> > rand;
	double drand48() { return rand(); }
};
