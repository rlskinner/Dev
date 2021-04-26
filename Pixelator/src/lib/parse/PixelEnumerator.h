#ifndef	_PixelEnumerator_h_
#define	_PixelEnumerator_h_
//
//  PixelEnumerator application class
//

#include	"seed.h"
#include	"action.h"
#include	"cellArray.h"
// #include	"glCellArray.h"
#if	IMAGE_SUPPORT
#include	<il/ilImage.h>
#endif

#if	IMAGE_SUPPORT
struct	fitZoom {
    ilImage	*img;
    fitZoom	*next;

    fitZoom( ilImage *_img )    { img = _img;  next = NULL; }
    ~fitZoom() { next = NULL; }
};
#endif

class	PixelEnumerator	{
protected:
    // options	*ops;
    seed	*seeds;
    action	*actions;

#if	IMAGE_SUPPORT
    fitZoom	*fitImages;
#endif

    //
    //  post-ops
    //
    int	writeFile;
    char	*writeFilename;
    int	exitWhenDone;

public:
    		PixelEnumerator( int argc, char **argv );
    virtual	~PixelEnumerator();

    		int	parseInput( int argc, char *argv[] );
		void	init();
		void	doActions( int block = 0 );
    virtual	void	makeCellArray( int nDim, int dims[] ) = 0;
    virtual	void	processEvent( int block = 0 ) = 0;

		void	addSeed( seed *s )      { s->next = seeds;  seeds = s; }
		void    addAction( action *a )  { a->next = actions;  actions = a; }

#if	IMAGE_SUPPORT
    		void	addZoomToFit( ilImage *img );
#endif
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

    int		argc;
    char	**argv;
    cellArray	*cells;

};

// vim:ts=8:
#endif	// _PixelEnumerator_h_
