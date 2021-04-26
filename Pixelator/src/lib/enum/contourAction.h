#ifndef	_contourAction_
#define	_contourAction_

#include	"action.h"

class	ContourAction : public Action 
    {
    protected:
	Weight	*m_primary;

	virtual	void	makeNbors();

    public:
	ContourAction( Weight *_primary, Weight *_wgt )
		: Action( _wgt )
	  	, m_primary(_primary)
		{ }

		virtual std::string name();

	virtual	void	init(/* Dimensions const& dims */);
	virtual void	doAction( CellArray *cells, Index const& index);
    };
	
#endif	/* _ContourAction_ */

