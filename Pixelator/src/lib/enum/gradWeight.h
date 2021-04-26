#ifndef	_gradWeight_h_
#define	_gradWeight_h_
//
//  weight function is the dot product of the relative position 
//	and the vector given by the two images
//		(or should it be two other arbitrary weight functions?)
//

#include	"weight.h"
#include	<il/ilImage.h>

class gradWeight : public Weight 
    {
    protected:
	weight	*m_delX, *m_delY;	// should these be other weights?
#ifdef	OLD_STYLE
	virtual double  getFunctionalWgt( int nDim, int abs[], int rel[] );
#endif

	//  optimized sqrt for integers
	int	sqrtTblLen;
	float	*sqrtTbl;
	float	sqrt( int d );

    public:
	gradWeight( Weight *delx, Weight *dely );
	virtual ~gradWeight();

	virtual	void	init( Dimensions const& dims[] );

	virtual void    getWgts( int nDim, int n, int abs[],
				 int *rel, float wgts[] );
    };
#endif	/* _gradWeight_h_ */

