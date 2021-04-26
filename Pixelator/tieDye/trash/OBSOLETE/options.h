#ifndef	_options_h_
#define	_options_h_

#include	"seed.h"
#include	"action.h"


struct	options {
	int	*dims; 			// requested size, may be ignored

	seed	*seeds;			// linked list of seeds

	action	*actions;		// linked list of actions

	//
	//  graphics startup options
	//
	int	setPosition;
	int	wx, wy;
	int	loadCmap;
	char	*cmapFilename;

	//
	//  post-ops
	//
	int	writeFile;
	char	*writeFilename;

	options();

	void	addSeed( seed *s )	{ s->next = seeds;  seeds = s; }
	void	addAction( action *a )	{ a->next = actions;  actions = a; }
};



//
//  find and parse an options file
//
options	*parseOptions( int argc, char *argv[] );

#endif	/* _options_h_ */
