#ifndef	_enContourWeight_h_
#define	_enContourWeight_h_
//
//  weight function is the dot product of the relative position 
//	and the vector given by the two images
//		(or should it be two other arbitrary weight functions?)
//

#include	"enWeight.h"
#include	<il/ilImage.h>

class enContourWeight : public enWeight {
protected:
    enWeight	*_contour;
    enWeight	*_scale;
    double	_dropoff;

public:
    enContourWeight( enWeight *contour, enWeight *scale, double dropoff );
    virtual ~enContourWeight();

    virtual	void	init( int nDim, int dims[] );

    virtual void    getWgts( int nDim, int n, int abs[],
				int *rel, float wgts[] );
};
#endif	/* _enContourWeight_h_ */
