#include	"app.h"
#include	"shapes.h"

#include	<stdio.h>
#include	<string.h>

#include	<strToArgs.h>

app::app()
{
    shape = NULL;
    slices = NULL;
    setShape( "sphere" );
}


void
app::init()
{
}


void
app::run()
{
    char	inBuf[BUFSIZ];

    while( gets(inBuf) != NULL ) {
	char	**argv;
	int	argc = strToArgs( inBuf, &argv );
	if( argc > 0 ) {
	    parse( argc, argv );
	    freeArgs( argv );
	} else {
	    printHelp();
	}
    }
}


void
app::printHelp()
{
    puts( "S STR:\tset rendering shape" );
    puts( "r N:\tset resolution (in cells, squared) of a slice" );
    puts( "M f:\tset major radius" );
    puts( "m f:\tset minor radius" );
    puts( "i f:\tset increment in minor radius between slices" );
    puts( "d N:\tset number of slices to display" );
    puts( "D N:\tset number of slices to save" );
    puts( "f f:\tset fade or decay per slice" );
    puts( "c N:\tset max bucket count to stop computing slice" );
    puts( "a f f:\tadd a slice at omega" );
    puts( "s:\tshift slices" );
    puts( "u:\tupdate display" );
    puts( "--- entering any command without a parameter"
    	    "prints the current value" );
    puts( "--- The current state:" );
    printState();
}


#define	PRINT_STATE_1( c, fmt, v )					\
	    case c : 							\
		printf( fmt, v );					\
		if( cmd != 0 ) break

#define	PRINT_STATE_2( c, fmt, v1, v2 )					\
	    case c : 							\
		printf( fmt, v1, v2 );					\
		if( cmd != 0 ) break

void
app::printState( char cmd )
{
    switch( cmd ) {
	case 0:				// print the entire state
	PRINT_STATE_1( 'S', "  3D shape = %s\n", shape );
	PRINT_STATE_1( 'r', "  slice resolution = %d\n", slices->resolution );
	PRINT_STATE_1( 'M', "  major radius = %g\n", slices->major );
	PRINT_STATE_1( 'm', "  minor radius = %g\n", slices->minor );
	PRINT_STATE_1( 'i', "  slice spacing = %g\n", slices->sliceInc );
	PRINT_STATE_1( 'd', "  display %d slices\n", slices->displayDepth );
	PRINT_STATE_1( 'D', "  save %d slices\n", slices->saveDepth );
	PRINT_STATE_1( 'f', "  fade constant = %g\n", slices->fade );
	PRINT_STATE_1( 'c', "  max bucket count = %d\n", slices->maxBucket );
	default:
	    break;
    }
}

#undef	PRINT_STATE_1
#undef	PRINT_STATE_2

#define	DO_COMMAND( setcmd ) 						\
	    if( argc == 1 ) setcmd ();					\
	    else errFlag = 1;						\
	    break

#define	SET_1_COMMAND( setcmd, v ) 					\
	    if( argc == 2 ) setcmd ( v );				\
	    if( argc == 2 || argc == 1 ) { printState( c ); }		\
	    else { errFlag = 1; }					\
	    break

#define	SET_2_COMMAND( setcmd, v1, v2 )					\
	    if( argc == 3 ) setcmd ( v1, v2 );				\
	    if( argc == 3 || argc == 1 ) { printState( c ); }		\
	    else { errFlag = 1; }					\
	    break

void
app::parse( int argc, char **argv )
{
    int	errFlag = 0;
    char c = argv[0][0];
    float	v1 = argc >= 2 ? atof( argv[1] ) : 0.0;
    float	v2 = argc >= 3 ? atof( argv[2] ) : 0.0;
    switch( c ) {
	case 'S': SET_1_COMMAND( setShape, argv[1] );
	case 'r': SET_1_COMMAND( slices->setResolution, int(v1) );
	case 'M': SET_1_COMMAND( slices->setMajorRadius, v1 );
	case 'm': SET_1_COMMAND( slices->setMinorRadius, v1 );
	case 'i': SET_1_COMMAND( slices->setSliceIncrement, v1 );
	case 'd': SET_1_COMMAND( slices->setDisplayDepth, int(v1) );
	case 'D': SET_1_COMMAND( slices->setSaveDepth, int(v1) );
	case 'f': SET_1_COMMAND( slices->setFade, v1 );
	case 'c': SET_1_COMMAND( slices->setMaxBucketCount, int(v1) );
	case 'a': SET_2_COMMAND( addSlice, v1, v2 );
	case 's': DO_COMMAND( slices->shift );
	case 'u': DO_COMMAND( slices->draw );
	case '?':
	    printHelp();
	    break;
	default:
	    errFlag = 1;
	    break;
    }

    if( errFlag ) {
	printHelp();
    }
}
#undef	SET_1_COMMAND
#undef	SET_2_COMMAND
#undef	DO_COMMAND

#define	SET_SHAPE( s, sLen, NAME )					\
    do {								\
	int	nLen = strlen( #NAME );					\
        if( strncmp( s, #NAME, sLen < nLen ? sLen : nLen ) == 0 ) {	\
	    if( shape == NULL || strcmp( shape, #NAME ) != 0 ) {	\
	        shape = #NAME;						\
		delete slices;						\
		slices = new NAME ();					\
		printf( "shape set to %s\n", #NAME );			\
	    } else {							\
		printf( "shape already set to %s\n", #NAME );		\
	    }								\
	    return;							\
	}								\
    } while( 0 )

void
app::setShape( char *s )
{
    int sLen = strlen( s );
    SET_SHAPE( s, sLen, sphere );
    printf( "sorry, no shape matches %s\n", s );
}

#undef	SET_SHAPE

void
app::addSlice( float o1, float o2 )
{
    printf( "add slice at %g, %g\n", o1, o2 );
}


int
main() 
{
    app	theApp;

    theApp.init();
    theApp.run();
}
