#ifndef	_diskSeed_
#define	_diskSeed_

#include	"seed.h"

class	DiskSeed : public Seed 
    {
    protected:
	int	m_cx, m_cy, m_radius;

    public:
	DiskSeed(int cx, int cy, int rad, Weight *wgt);

	virtual std::string name();

	virtual void	seedArray(CellArray *cells, Dimensions const& dims);
    };
	
#endif	/* _DiskSeed_ */

// vim:ts=8:
