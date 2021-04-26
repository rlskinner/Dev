#ifndef	_constWeight_h_
#define	_constWeight_h_

//
//  define a abstract weight class that can change the constWeight based
//	on location (absolute or relative), or history, etc.
//

#include	"weight.h"

class	constWeight : public weight {
protected:
public:
	constWeight( double w ) { isConst = 1;  constWgt = w; }
	virtual	~constWeight() {}
};

#endif	/* _constWeight_h_ */
