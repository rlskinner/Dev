//
//  A class that records time and takes differences 
//

#ifdef	WIN32
#include	<Winsock2.h>
#else // !WIN32
#include	<sys/time.h>
#endif // !WIN32


class	Timer {
public:
	Timer();
	~Timer();

	void	mark();			// mark the current time
	float	diff( const Timer &other );	// return elapsed time.

protected:
	timeval	time;
};
