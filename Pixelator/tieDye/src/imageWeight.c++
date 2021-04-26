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


void
imageWeight::init( int _nDim, int _dims[] )
{
	nDim = _nDim;
	dims = new int[nDim];
	for( int i=0; i<nDim; i++ ) dims[i] = _dims[i];

	imgData = new float[dims[0]*dims[1]];
	ilConfig	config( iflFloat, iflInterleaved, 1 );
	image->getTile( 0, 0, dims[0], dims[1], imgData, &config );
}


void
imageWeight::getWgts( int nDim, int n, int abs[], int *rel, float wgts[] )
{
    for( int i=0; i<n; i++, rel += nDim ) {
	wgts[i] = imgData[(abs[1]+rel[1])*dims[0] + (abs[0]+rel[0])];
    }
}

