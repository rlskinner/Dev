#ifndef	_TORUSTABLEATTRACTOR_H__
#define	_TORUSTABLEATTRACTOR_H__
//
//  define an ADT that implements the torus attractor mapping
//

#include	"TorusAttractor.h"
#include	<interval.h>

#define	NUM_COEFFS	4

class	TorusTableAttractor : public TorusAttractor {
public:
    TorusTableAttractor( int xCellRes, int yCellRes );
    ~TorusTableAttractor();

    virtual     void    randomizeArrays();
    virtual	void	resetParameters();	// recomputes p1, p2 arrays

private:
    float	*p1Array, *p2Array;
    int		xCellRes, yCellRes;
    void	allocateP1P2Arrays();
    void	computeP1P2Arrays();

    virtual	void	computeP1P2( double theta, double psi, 
				double *p1, double *p2 );
    virtual	void	computeRange( const Interval &omega, 
				const Interval &eps, 
				const Interval &param, Interval &theta );
};

#endif	/* _TORUSTABLEATTRACTOR_H__ */
