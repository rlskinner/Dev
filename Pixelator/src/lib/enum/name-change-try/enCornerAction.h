#ifndef	_enCornerAction_
#define	_enCornerAction_

#include	<stdio.h>

#include	"enAction.h"

class	enCornerAction : public enAction {
protected:
    virtual	void	makeNbors();
public:
	enCornerAction( enWeight *wgt ) 
		: enAction( wgt )
		{}

};
	
#endif	/* _enCornerAction_ */
