#ifndef	_enConstWeight_h_
#define	_enConstWeight_h_

//
//  define a abstract weight class that can change the constWeight based
//	on location (absolute or relative), or history, etc.
//

#include	"enWeight.h"

class	enConstWeight : public enWeight {
protected:
public:
	enConstWeight( double w ) { isConst = 1;  constWgt = w; }
	virtual	~enConstWeight() {}
};

#endif	/* _enConstWeight_h_ */
