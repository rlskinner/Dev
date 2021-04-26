//
//   PixelEnumerator an image away based on different rules, and different seed points
//

#include	<stdio.h>
#include	<stdlib.h>
// #include	<unistd.h>
// #include        <libc.h>
#include        <string.h>

// #include	<il/ilFileImg.h>
// #include	<il/ilRotZoomImg.h>

#include	"PixelEnumerator.h"

PixelEnumerator::PixelEnumerator( int _argc, char **_argv )
{
    dims = NULL;
    cells = NULL;
    seeds = NULL;
    actions = NULL;
//     fitImages = NULL;

    setPosition = FALSE;
    loadCmap = FALSE;
    cmapFilename = NULL;
    writeFile = FALSE;
    writeFilename = NULL;
    exitWhenDone = FALSE;

    argc = _argc;
    argv = _argv;
}


PixelEnumerator::~PixelEnumerator()
{
}


extern  "C"     void yyparse();

int	
PixelEnumerator::parseInput( int argc, char *argv[] )
{
	// find the file if possible
	if( argc > 1 ) {
		int	f = open( argv[1], 0 );
		if( f >= 0 ) {
			int	si = dup( 0 );		// save stdin
			dup2( f, 0 );			// make file stdin
			yyparse();
			close( 0 );
			close( f );
			dup2( si, 0 );			// restore old stdin
			return 0;
		} else {
			fprintf( stderr, "error opening options file %s\n",
				argv[1] );
			return 1;
		}
	}

	yyparse();
	return 0;
}


void	
PixelEnumerator::init()
{
#if	IMAGE_SUPPORT
    fitZoom	*fz = fitImages;
    while( fz != NULL ) {
	ilRotZoomImg    *rz = (ilRotZoomImg*)fz->img;
	rz->sizeToFit( dims[0], dims[1] );
	fz = fz->next;
    }
#endif

    // 
    //  first, reverse the order of the seeds and actions,
    //	so that they will be executed in the order given in
    //	the script.
    //
    seed	*newSeeds = NULL;
    while( seeds != NULL ) {
	seed	*s = seeds;		// remove from original list
	seeds = seeds->next;
	s->next = newSeeds;		// place on new list
	newSeeds = s;
    }
    seeds = newSeeds;			// replace reordered list

    action	*newActions = NULL;
    while( actions != NULL ) {
	action	*a = actions;		// remove from original list
	actions = actions->next;
	a->next = newActions;		// place on new list
	newActions = a;
    }
    actions = newActions;		// replace reordered list


    //  
    //  init cells, seeds, and actions 
    //
    makeCellArray( 2, dims );
    cells->init( this );
    seed	*s = seeds;
    while( s != NULL ) {
	s->init( 2, dims );
    	s->seedArray( cells, 2, dims );
    	s = s->next;
    }
    action	*a = actions;
    while( a != NULL ) {
    	a->init( 2, dims );
    	a = a->next;
    }

    
}


//
//  do at most 100 pixels and return
//
void	
PixelEnumerator::doActions( int block )
{
    int	count = 100;
    while( cells->numWaiting() > 0 && count > 0 ) {

    	int	index[2];
    	cells->pick( index );
    	action	*a = actions;
    	while( a != NULL ) {
    		a->doAction( cells, index );
    		a = a->next;
    	}

    	count--;
    }
}


#if	IMAGE_SUPPORT
void	
PixelEnumerator::addZoomToFit( ilImage *img )
{
    fitZoom	*fz = new fitZoom( img );
    fz->next = fitImages;
    fitImages = fz;
}
#endif


void
PixelEnumerator::setSize( int sx, int sy )
{
    delete dims;
    dims = new int[2];
    dims[0] = sx;
    dims[1] = sy;

}


void
PixelEnumerator::setSize( int sx, int sy, int px, int py )
{
    delete dims;
    dims = new int[2];
    dims[0] = sx;
    dims[1] = sy;

    setPosition = 1;
    wx = px;
    wy = py;
}


void
PixelEnumerator::loadColormap( char *file )
{
    loadCmap = 1;
    cmapFilename = strdup( file );
}


void
PixelEnumerator::setWriteImage( char *file, char * /*type */ )
{
    writeFile = 1;
    writeFilename = strdup( file );
}


#if	IMAGE_SUPPORT
void
PixelEnumerator::writeImage()
{
    if( !writeFile )
	return;

    iflFileConfig cfg( new iflSize( dims[0], dims[1], 1 ), 
    			iflLong, iflInterleaved, iflRGBPalette );
    ilFileImg 	*img = new ilFileImg( writeFilename, NULL, &cfg );

    long	*buf = new long[dims[0]];
    for( int j=0; j<dims[1]; j++ ) {
	for( int i=0; i<dims[0]; i++ ) {
	    if( cells->states[i+j*dims[0]] == csFilled ) {
		buf[i] = cells->cellData[i+j*dims[0]].fillOrder;
	    } else {
		buf[i] = 0;
	    }
	}
        img->setTile( 0, j, dims[0], j+1, buf );
    }
    delete img;
    delete buf;
}
#endif

	


// vim:ts=8:
