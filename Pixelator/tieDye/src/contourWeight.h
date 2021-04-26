#ifndef	_contourWeight_h_
#define	_contourWeight_h_
//
//  weight function is the dot product of the relative position 
//	and the vector given by the two images
//		(or should it be two other arbitrary weight functions?)
//

#include	"weight.h"
#include	<il/ilImage.h>

class contourWeight : public weight {
protected:
    weight	*contour;
    weight	*scale;
    double	dropoff;

public:
    contourWeight( weight *contour, weight *scale, double dropoff );
    virtual ~contourWeight();

    virtual	void	init( int nDim, int dims[] );

    virtual void    getWgts( int nDim, int n, int abs[],
				int *rel, float wgts[] );
};
#endif	/* _contourWeight_h_ */
