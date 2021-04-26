#ifndef	_seed_
#define	_seed_

#include	<stdio.h>
#include	<string>

#include	"weight.h"

class	CellArray;
class	Dimensions;

class	Seed 
    {
    protected:
		Weight	*m_wgt;

    public:
		Seed	*m_next;
		Seed( Weight *_wgt )		{ m_wgt = _wgt; m_next = NULL; }

		virtual std::string name() = 0;

		virtual	void	init(Dimensions const& dims);

		virtual void	seedArray(CellArray *cells, Dimensions const& dims) = 0;
    }; // class Seed
	
#endif	/* _seed_ */

