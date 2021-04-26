#ifndef	_enImageSeed_
#define	_enImageSeed_

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

	virtual void	seedArray( enCellArray *cells, int nDim, int dims[] );
};
	
#endif	/* _enImageSeed_ */
