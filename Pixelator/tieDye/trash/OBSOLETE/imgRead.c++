//
//   eat an image away based on different rules, and different seed points
//

#include	<stdio.h>
#include	<math.h>

#include	<string.h>
#include	<il/ilImage.h>
#include	<il/ilGenericImgFile.h>


main( int argc, char *argv[] )
{
	int	row = 0;
	int	col = 0;
	int	ran = 0;
	char	*filename;

	if( argc < 3 || argc < 2 ) {
		fprintf( stderr, "usage: imgRead [-x|-y|-r] imageFile\n" );
		exit( 1 );
	} else if( argc == 2 ) {
		row = 1;
		filename = argv[1];
	} else if( argc == 3 ) {
		filename = argv[2];
		if( strcmp( argv[1], "-x" ) == 0 ) 
			row = 1;
		if( strcmp( argv[1], "-y" ) == 0 ) 
			col = 1;
		if( strcmp( argv[1], "-r" ) == 0 ) 
			ran = 1;
	}

	//
	// open image filename
	//
	ilImage *img = ilOpenImgFile( filename, "r" );
	long	nx = img->getXsize();
	long	ny = img->getYsize();

	ilPixel pix;
	if( row ) {
	    for( int j=0; j<ny; j++ ) {
		for( int i=0; i<nx; i++ ) {
			img->getPixel( i, j, pix );
		}
	    }
	}

	if( col ) {
	    img->setCacheWindow( nx/4, ny );
	    for( int i=0; i<nx; i++ ) {
		for( int j=0; j<ny; j++ ) {
			img->getPixel( i, j, pix );
		}
	    }
	}

	if( ran ) {
		img->setCacheWindow( nx, ny );
		int	num = nx*ny;
		for( int n=0; n<num; n++ ) {
			int	i = random() % nx;
			int	j = random() % ny;
			img->getPixel( i, j, pix );
		}
	}

}


