#ifndef	_linearWeight_h_
#define	_linearWeight_h_

//
//  define a abstract weight class that can change the linearWeight based
//	on location (absolute or relative), or history, etc.
//

#include	"weight.h"

class	linearWeight : public weight {
protected:
public:
	linearWeight();
	virtual	~linearWeight();
};

#endif	/* _linearWeight_h_ */

// vim:ts=8:
