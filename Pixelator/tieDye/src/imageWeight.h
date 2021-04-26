#ifndef	_imageWeight_h_
#define	_imageWeight_h_

//
//  define a abstract weight class that can change the imageWeight based
//	on location (absolute or relative), or history, etc.
//

#include	"weight.h"
#include	"il/ilImage.h"

class	imageWeight : public weight {
protected:
	ilImage	*image;
#ifdef	OLD_STYLE
	double	getFunctionalWgt( int nDim, int abs[], int rel[] );
#endif

	int	nDim;
	int	*dims;
	float	*imgData;

public:
	imageWeight( ilImage *img );
	virtual	~imageWeight();

	virtual	void	init( int nDim, int dims[] );

	virtual void    getWgts( int nDim, int n, int abs[],
					int *rel, float wgts[] );
};

#endif	/* _imageWeight_h_ */
