#pragma	once
/*
 *  routines in ~/lib/src/rand.c
 */

#ifdef	__cplusplus
extern	"C" {
#endif

double gauss();
double uniRandom( float low, float high );


#ifdef	__cplusplus
}
#endif

//
// Unix replacement in ~/lib/src/drand48.cpp
//
double drand48();
