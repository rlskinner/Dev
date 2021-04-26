#ifndef	_nborAction_
#define	_nborAction_

#include	"action.h"

class	nborAction : public action {
protected:
	int	connectedness;

	virtual	void	makeNbors();
public:
	nborAction( weight *wgt, int connect );
};
	
#endif	/* _nborAction_ */
