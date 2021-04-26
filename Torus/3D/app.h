//
//  3D torus application
//


#include <math.h>
#define PI2     (2 * M_PI)

#include	"sliceSeq.h"

extern  float omega1;
extern  float omega2;
extern  float epsilon;

#ifdef  __cplusplus
extern "C" {
    void        makeMap( unsigned char *buf, int size, int maxCount );
    void        setEpsilon( float );
}
#endif


//
//  application for imaging torus in 3D
//
class	app {
protected:
    char	*shape;
    sliceSeq	*slices;

    void	setShape( char *s );
    void	addSlice( float o1, float o2 );

    void	parse( int argc, char **argv );
    void	printHelp();
    void	printState( char variable = 0 );
public:
    app();
    
    void	init();
    void	run();
};
