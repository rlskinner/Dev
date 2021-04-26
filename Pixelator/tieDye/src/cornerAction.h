#ifndef	_cornerAction_
#define	_cornerAction_

#include	<stdio.h>

#include	"action.h"

class	cornerAction : public action {
protected:
    virtual	void	makeNbors();
public:
	cornerAction( weight *wgt ) 
		: action( wgt )
		{}

};
	
#endif	/* _cornerAction_ */
