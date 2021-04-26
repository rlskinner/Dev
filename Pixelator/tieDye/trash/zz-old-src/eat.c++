//
//   eat an image away based on different rules, and different seed points
//

#include	<stdio.h>
#include	<stdlib.h>
#include	<unistd.h>
#include        <libc.h>
#include        <string.h>

#include	<il/ilGenericImgFile.h>
#include	<il/ilRotZoomImg.h>

#include	"eat.h"

eat	*eatApp;

eat::eat()
{
    dims = NULL;
    cells = NULL;
    seeds = NULL;
    actions = NULL;
    fitImages = NULL;

    setPosition = FALSE;
    loadCmap = FALSE;
    cmapFilename = NULL;
    writeFile = FALSE;
    writeFilename = NULL;
    exitWhenDone = FALSE;
}


eat::~eat()
{
}


extern  "C"     void yyparse();

int	
eat::parseInput( int argc, char *argv[] )
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
eat::init()
{
    fitZoom	*fz = fitImages;
    while( fz != NULL ) {
	ilRotZoomImg    *rz = (ilRotZoomImg*)fz->img;
	rz->sizeToFit( dims[0], dims[1] );
	fz = fz->next;
    }

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


void	
eat::doActions( int block )
{
    cells->print();
    while( cells->numWaiting() > 0 ) {

    	int	index[2];
    	cells->pick( index );
    	action	*a = actions;
    	while( a != NULL ) {
    		a->doAction( cells, index );
    		a = a->next;
    	}

    	processEvent();
    }
    writeImage();			// XXX doesn't seem belong here

    if( !exitWhenDone ) 
	processEvent( block );
}


void	
eat::addZoomToFit( ilImage *img )
{
    fitZoom	*fz = new fitZoom( img );
    fz->next = fitImages;
    fitImages = fz;
}


void
eat::setSize( int sx, int sy )
{
    delete dims;
    dims = new int[2];
    dims[0] = sx;
    dims[1] = sy;

}


void
eat::setSize( int sx, int sy, int px, int py )
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
eat::loadColormap( char *file )
{
    loadCmap = 1;
    cmapFilename = strdup( file );
}


void
eat::setWriteImage( char *file, char *type )
{
    writeFile = 1;
    writeFilename = strdup( file );
}


void
eat::writeImage()
{
    if( !writeFile )
	return;

    ilSize	size( dims[0], dims[1], 1 );
    ilFileImg 	*img = ilCreateImgFile( writeFilename,
					size, ilLong, ilSequential, ilFIT_IMG,
					NULL );

    img->setTile( 0, 0, dims[0], dims[1], cells->data );
    delete img;
}

	

