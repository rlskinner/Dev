#include	"weight.h"

//
//  define a anstract weight class that can change the weight based
//	on location (absolute or relative), or history, etc.
//

weight::~weight() {}

void weight::init( int, int[] ) {}

double	weight::getFunctionalWgt( int, int [], int [] )
{
	return 0.0;
}

