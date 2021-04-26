#ifndef	_cornerAction_
#define	_cornerAction_

#include	<stdio.h>

#include	"action.h"

class	CornerAction : public Action 
    {
    protected:
	virtual	void	makeNbors();

    public:
	CornerAction( Weight *wgt ) 
	    : Action( wgt )
	    {}

		virtual std::string name();

    };
	
#endif	/* _CornerAction_ */

