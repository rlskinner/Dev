//
//  screen saver using TorusAttractor and TorusTiler
//

#include	<GraphicsApp.h>
#include	<sys/time.h>
#include	<stdlib.h>
#include	<math.h>
#include	<gl/device.h>

int
main( int argc, char *argv[] )
{
    struct timeval time;
    gettimeofday( &time );
    srand48( time.tv_sec );
    srandom( time.tv_sec );

    GraphicsApp	*app = (GraphicsApp*)makeDefaultApplication();

    if( app->parseArgs( argc, argv ) ) {
	return( 1 );
    }

    app->init();

    while( 1 ) {
	
	//
	//  print out contents of event queue for now
	//
	while( qtest() ) {
	    short	data;
	    long	event = qread( &data );
	    // printf( "event = %d, data = %d\n", event, data );
	    if( event == REDRAW ) {
		app->redraw();
	    }
	}

	app->doFrame();
    }
}


