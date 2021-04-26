#ifndef	_enLinearWeight_h_
#define	_enLinearWeight_h_

//
//  define a abstract enWeight class that can change the linearWeight based
//	on location (absolute or relative), or history, etc.
//

#include	"enWeight.h"

class	linearWeight : public enWeight {
protected:
public:
	linearWeight();
	virtual	~linearWeight();
};

#endif	/* _enLinearWeight_h_ */
