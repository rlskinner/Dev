#include	"weight.h"

//
//  define a anstract weight class that can change the weight based
//	on location (absolute or relative), or history, etc.
//

weight::~weight() {}

void weight::init( int, int[] ) {}

void
weight::getWgts( int, int n, int[], int[], float wgts[] )
{
    for( int i=0; i<n; i++ ) wgts[i] = constWgt;
}

