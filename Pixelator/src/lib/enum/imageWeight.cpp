#include "imageWeight.h"

//
//  define a abstract weight class that can change the imageWeight based
//	on location (absolute or relative), or history, etc.
//

imageWeight::imageWeight( ilImage *img )
{
	image = img;
	nDim = 0;
	dims = NULL;
}


imageWeight::~imageWeight()
{
	delete image;		// XXX is there reference counting?
	delete imgData;
}


// 
// Initialize the imageWeight from the cell array dimensions
//
void imageWeight::init(int nDim, // # dimensions
		       int dims[] // actual dimensions
		      )
{
	nDim = nDim;
	dims = new int[nDim];
	for( int i=0; i<nDim; i++ ) dims[i] = dims[i];

	imgData = new float[dims[0]*dims[1]];
	ilConfig	config( iflFloat, iflInterleaved, 1 );
	image->getTile( 0, 0, dims[0], dims[1], imgData, &config );
}


//
// Get an array of weights for the given array of indexes
// 	imageWeight gets weights directly from an image
//
void imageWeight::getWgts(int nDim, // # dimensions
			  int n, // number of indexes
			  int absIndexes[], // list of absolute indexes [n]
			  int relIndexes[], // list of relative indexes [n]
			  double wgts[] // out: weights [n]
			 )
{
    for( int i=0; i<n; i++, rel += nDim ) {
	wgts[i] = imgData[(abs[1]+rel[1])*dims[0] + (abs[0]+rel[0])];
    }
}


// vim:ts=8:
