#ifndef	_enNborAction_
#define	_enNborAction_

#include	"enAction.h"

class	nborAction : public enAction {
protected:
	int	connectedness;

	virtual	void	makeNbors();
public:
	nborAction( enWeight *wgt, int connect );
};
	
#endif	/* _enNborAction_ */
