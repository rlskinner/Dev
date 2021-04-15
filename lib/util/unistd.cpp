/*
 * Emulate functions declared in unistd.h
 */

#include	<windows.h>

extern	"C" {

    // call equivalent Windows function
    unsigned int sleep(unsigned int seconds)
	{
	Sleep(1000*seconds); // milliseconds
	return 0;
	}

}; // extern "C"

