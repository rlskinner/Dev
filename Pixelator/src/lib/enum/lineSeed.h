#ifndef	_lineSeed_
#define	_lineSeed_

#include	"seed.h"

class	LineSeed : public Seed 
    {
    protected:
	double	m_x0, m_y0, m_x1, m_y1;

    public:
	LineSeed( double x0, double y0, double x1, double y1, Weight *wgt );

	virtual std::string name();

	virtual void	seedArray( CellArray *cells, Dimensions const& dims);
    };
	
#endif	/* _LineSeed_ */

// vim:ts=8:
