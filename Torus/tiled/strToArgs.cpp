//
//  break a string into null-terminated argv/argc style input
//

#include	<strToArgs.h>

#include	<stdlib.h>
#include	<string.h>
#include	<ctype.h>


int
strToArgs( const char *str, char ***retArgv )
{
    int	argc = 0;
    char	**argv;
    
    const char *s = str;
    while( 1 ) {
	while( *s && isspace( *s ) ) s++;	// skip over spaces

	if( !*s ) break;;			// end of string

	if( argc == 0 ) {
	    argv = new char *[2];
	} else {
	    char **newArgv = new char*[argc+2];
	    for( int i=0; i<argc; i++ ) {
		newArgv[i] = argv[i];
	    }
	    delete argv;
	    argv = newArgv;
	}
	argv[argc] = (char *)s;
	argv[argc+1] = NULL;
	argc++;

	while( !isspace( *s ) && *s ) s++;
    }

    //
    //  now make a second pass and dup words
    //
    for( int i=0; i<argc; i++ ) {
	int	len;
	if( argv[i+1] != NULL ) {
	    len = argv[i+1]-argv[i];
	} else {
	    len = strlen( argv[i] );
	}

	char	*s = new char[len+1];
	strncpy( s, argv[i], len );
	s[len] = 0;
	while( len > 0 && isspace(s[len-1]) ) {
	    s[len-1] = 0;
	    len--;
	}
	argv[i] = s;
    }

    *retArgv = argv;
    return argc;
}


void
freeArgs( char **argv )
{
    char **s = argv;

    while( *s ) {
	delete *s;
	s++;
    }

    delete argv;
}



