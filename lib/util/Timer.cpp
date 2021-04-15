//
//  A class that records time and takes differences 
//

#include	"Timer.h"

Timer::Timer()
{
	time.tv_sec = 0;
	time.tv_usec = 0;
}



Timer::~Timer()
{
	time.tv_sec = 0;
	time.tv_usec = 0;
}




// mark the current time
void	
Timer::mark()
{
#if WIN32
	// we only measure elapsed time, so GetTickCount is OK.
	// GetTickCount wraps around every 49.7 days, but when was the last
	// time you saw a Windows machine run that long?
	DWORD msecTicks = GetTickCount();
	time.tv_sec = msecTicks / 1000;
	time.tv_usec = 1000*(msecTicks % 1000);
#else // !WIN32
	gettimeofday( &time, 0 );
#endif // !WIN32
}





// return elapsed time.
float	
Timer::diff( const Timer &other )
{
	float	delta = time.tv_sec - other.time.tv_sec;
	delta += (time.tv_usec - other.time.tv_usec)/1000000.0;

	return delta;
}



