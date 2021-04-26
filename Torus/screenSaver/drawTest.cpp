#include	<Timer.h>
#include	<gl/gl.h>
#include	<math.h>
#include	<stdio.h>

const	int	numFrames = 100;
const	int	numPoints = 10000;

struct	position {
	short	x, y;
};


position	randomPoints[numPoints];

void
makeRandomPoints( int imageWidth, int imageHeight )
{
    for( int i=0; i<numPoints; i++ ) {
	randomPoints[i].x = short(random() % imageWidth);
	randomPoints[i].y = short(random() % imageHeight);
    }
}


unsigned long	colors[] = {
		    0xff0000ff,
		    0xff00ffff,
		    0xff00ff00,
		    0xffffff00,
		    0xffff0000,
		    0xffff00ff,
};
int	colorUsed = 0;

unsigned long
getNextColor()
{
    int	lastColor = colorUsed;
    colorUsed = (colorUsed+1) % (sizeof(colors)/sizeof(unsigned long));
    return colors[lastColor];
}


position*
makeOffsets( int imageWidth, int imageHeight, int columns, int rows )
{
    position	*offsets = new position[columns*rows];

    int	n = 0;
    for( int i=0; i<columns; i++ ) {
	for( int j=0; j<rows; j++ ) {
	    offsets[n].x = i*imageWidth;
	    offsets[n].y = j*imageHeight;
	    n++;
	}
    }
    return offsets;
}

float
pointsTest( int imageWidth, int imageHeight, int columns, int rows )
{
    position	*offsets = makeOffsets( imageWidth, imageHeight, columns, rows);

    cpack( 0xff000000 );
    clear();

    int	numTiles = columns*rows;
    Timer	startTest;
    startTest.mark();
    for( int frame=0; frame<numFrames; frame++ ) {
	cpack( getNextColor() );
	for( int point=0; point<numPoints; point++ ) {
	    bgnpoint();
	    for( int tile=0; tile<numTiles; tile++ ) {
		short	v[2];
		v[0] = randomPoints[point].x + offsets[tile].x;
		v[1] = randomPoints[point].y + offsets[tile].y;
		v2s( v );
	    }
	    endpoint();
	}
    }
    Timer	endTest;
    endTest.mark();

    delete offsets;

    return endTest.diff( startTest );

}

float
copyTest( int smart, int imageWidth, int imageHeight, int columns, int rows )
{
    Timer	startTest;
    startTest.mark();

    cpack( 0xff000000 );
    clear();

    for( int frame=0; frame<numFrames; frame++ ) {
	cpack( getNextColor() );

	//  do first tile
	bgnpoint();
	for( int point=0; point<numPoints; point++ ) {
	    short	v[2];
	    v[0] = randomPoints[point].x;
	    v[1] = randomPoints[point].y;
	    v2s( v );
	}
	endpoint();

	if( smart ) {
	    //  do 5x4 tiles
	    rectcopy( 0, 0, imageWidth-1, imageHeight-1, 0, imageHeight );
	    rectcopy( 0, 0, imageWidth-1, 2*imageHeight-1, 0, 2*imageHeight );
	    rectcopy( 0, 0, imageWidth-1, 4*imageHeight-1, imageWidth, 0 );
	    rectcopy( 0, 0, 2*imageWidth-1, 4*imageHeight-1, 2*imageWidth, 0 );
	    rectcopy( 0, 0, imageWidth-1, 4*imageHeight-1, 4*imageWidth, 0 );
	} else {
	    for( int i=0; i<columns; i++ ) {
		for( int j=0; j<rows; j++ ) {
		    if( !(i == 0 && j == 0) ) {
			rectcopy( 0, 0, imageWidth-1, imageHeight-1,
				i*imageWidth, j*imageHeight );
		    }
		}
	    }
	}
    }
    
    Timer	endTest;
    endTest.mark();
    return endTest.diff( startTest );
}


void
doPerformanceTest( int imageWidth, int imageHeight, int columns, int rows )
{
    makeRandomPoints( imageWidth, imageHeight );
    float pointsTime = pointsTest( imageWidth, imageHeight, columns, rows );
    float bruteCopyTime = copyTest( 0, imageWidth, imageHeight, columns, rows );
    float smartCopyTime = copyTest( 1, imageWidth, imageHeight, columns, rows );

    printf( "=============== %d x %d ===============\n", 
		imageWidth, imageHeight );
    printf( "drawing points: %.3g\n", pointsTime );
    printf( "copying blocks (brute): %.3g\n", bruteCopyTime );
    printf( "copying blocks (smart): %.3g\n", smartCopyTime );
}

main()
{
    //
    // set up for 640x512 pixels, 5x4 tiling
    //
    foreground();
    prefposition( 0, 639, 1023-511, 1023 );
    winopen( "drawing performance test" );
    RGBmode();
    // doublebuffer();
    gconfig();

    ortho2(-0.5,640-0.5,-0.5,512-0.5);
    doPerformanceTest( 128, 128, 5, 4 );

    //
    //  set up for 1280x1024, 5x4
    //
    prefposition( 0, 1279, 0, 1023 );
    winconstraints();

    ortho2(-0.5,1280-0.5,-0.5,1024-0.5);
    reshapeviewport();
    doPerformanceTest( 256, 256, 5, 4 );

}


