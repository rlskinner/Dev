//
// Unix replacement for drand48()
//
#include 	"randomUtil.h"

#include	<boost/random/uniform_real.hpp>
#include	<boost/random/uniform_01.hpp>
#include	<boost/random/linear_congruential.hpp>
#include	<boost/random/variate_generator.hpp>

// 
// Implement drand48():  return random real in range [0,1)
double drand48()
	{
	static boost::rand48 rng;
	static boost::uniform_real<> uni_01(0, 1);
	static boost::variate_generator<boost::rand48&, boost::uniform_real<> > rand(rng, uni_01);

	return rand();
	}
