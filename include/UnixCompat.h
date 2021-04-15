#ifndef _UnixCompat_h_
#define _UnixCompat_h_

#include	<float.h>
#include	<math.h>
#include	<memory.h>
#include	<stdlib.h>

//
// Unix compatibility typdefs
//
typedef unsigned char u_char;

//
// compatibility functions
//
inline void bcopy(void *src, void *dest, size_t count)
	{
	memcpy(dest, src, count);
	}


//
//  Unix rint
//
inline double rint(double v)
	{
	return floor(v + 0.5);
	}


//
//  round to integer: int(rint)
//
inline int roundToInt(double v)
	{
	return int(rint(v));
	}


// 
//  NOTE:  Windoze is remarkably weak WRT random number generation.  
//  Its only functions are
//
// 		rand() -- returns a random integer in the range [0,0x7fff]
// 		seed(int seedval) -- seeds the random number generator.
//
//  * the range of values returned by rand() is small -- if your desired range
//  (size) is > 0x7fff, then some values will never be chosen.  If the desired
//  range (size) is < 0x7fff, but not << 0x7fff, then some values will be
//  overrepresented.  E.g. for [0,(2/3)*0x7fff], then the values in the first
//  half of range are twice as likely to be chosen as those in the second half.
//
//  * rand() is (in)famous for not being very random.
//

// 
// random number in an integer range: [lower, upper]
//
inline double randomInRange(int lower, int upper)
	{
	int randVal = rand();
	return lower + (upper-lower)*randVal/RAND_MAX;
	}


// 
// random number in a float range: [lower, upper]
//
inline double randomInRange(double lower, double upper)
	{
	int randVal = rand();
	return lower + (upper-lower)*randVal/RAND_MAX;
	}


#endif // _UnixCompat_h_

