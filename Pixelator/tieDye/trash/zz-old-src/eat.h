//
//  eat application class
//

#include	"seed.h"
#include	"action.h"
#include	"cellArray.h"
#include	"glCellArray.h"
#include	<il/ilImage.h>

struct	fitZoom {
    ilImage	*img;
    fitZoom	*next;

    fitZoom( ilImage *_img )    { img = _img;  next = NULL; }
    ~fitZoom() { next = NULL; }
};

class	eat	{
protected:
    cellArray	*cells;
    // options	*ops;
    seed	*seeds;
    action	*actions;

    fitZoom	*fitImages;

    //
    //  post-ops
    //
    int	writeFile;
    char	*writeFilename;
    int	exitWhenDone;

public:
    		eat();
    virtual	~eat();

    		int	parseInput( int argc, char *argv[] );
		void	init();
		void	doActions( int block = 0 );
    virtual	void	makeCellArray( int nDim, int dims[] ) = 0;
    virtual	void	processEvent( int block = 0 ) = 0;

		void	addSeed( seed *s )      { s->next = seeds;  seeds = s; }
		void    addAction( action *a )  { a->next = actions;  actions = a; }

    		void	addZoomToFit( ilImage *img );
		void	setSize( int sx, int sy );
		void	setSize( int sx, int sy, int px, int py );
		void	loadColormap( char *file );

		void	setWriteImage( char *file, char *type );
		void	writeImage();
		void	setExit() { exitWhenDone = 1; }

    //
    //  graphics startup options
    //
    int		*dims;			// requested cellArray dimensions
    int	setPosition;
    int	wx, wy;
    int	loadCmap;
    char	*cmapFilename;

};

extern	eat	*eatApp;
