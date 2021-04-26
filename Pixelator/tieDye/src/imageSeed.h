#ifndef	_imageSeed_
#define	_imageSeed_

#include	"seed.h"
#include	<il/ilImage.h>

class	imageSeed : public seed {
protected:
	ilImage	*img;
	int	toFit;
	int	scale;
	double	sx, sy;

public:
	imageSeed( ilImage *img, int tofit );
	imageSeed( ilImage *img, double sx, double sy );
	~imageSeed();

	virtual void	seedArray( cellArray *cells, int nDim, int dims[] );
};
	
#endif	/* _imageSeed_ */
