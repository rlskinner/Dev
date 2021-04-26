#ifndef	_ringAction_
#define	_ringAction_

#include	"action.h"

class	RingAction : public Action 
    {
    protected:
	int	m_radius;

	virtual	void	makeNbors();

    public:
	RingAction( Weight *wgt, int rad );

	virtual std::string name();

	virtual	void	init(/* Dimensions const& dims */);
    };
	
#endif	/* _ringAction_ */

// vim:ts=8:
