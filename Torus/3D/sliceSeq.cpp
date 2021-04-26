//
//  slice list:  manage and draw a list of slices
//

#include	"sliceSeq.h"
#include	<stdio.h>

//
//  true slice defaults
//
sliceSeq::sliceSeq()
{
    resolution = 100;
    maxBucket = 10;

    major = 1.0;
    minor = 0.1;
    sliceInc = .005;
    fade = .05;

    displayDepth = 16;
    saveDepth = 16;

puts( "allocate slice memory and geometry" );
}

sliceSeq::sliceSeq( sliceSeq &other )
{
    resolution = other.resolution;
    maxBucket = other.maxBucket;

    major = other.major;
    minor = other.minor;
    sliceInc = other.sliceInc;
    fade = other.fade;

    displayDepth = other.displayDepth;
    saveDepth = other.saveDepth;

puts( "copy slice memory and allocate geometry" );
}

//
// its square
//
void
sliceSeq::setResolution( int res )
{
    resolution = res;
puts( "recompute slices & geometry in memory at new resolution" );
}

void
sliceSeq::setMaxBucketCount( int n )
{
    maxBucket = n;
puts( "recompute slices" );
}

void
sliceSeq::setMajorRadius( float _major )
{
    major = _major;
puts( "recompute geometry" );
}

void
sliceSeq::setMinorRadius( float _minor )
{
    minor = _minor;
puts( "recompute geometry" );
}

void
sliceSeq::setSliceIncrement( float inc )
{
    sliceInc = inc;
puts( "recompute geometry" );
}

//
// reduce intensity per slice
//
void
sliceSeq::setFade( float a )
{
    fade = a;
}

void
sliceSeq::setDisplayDepth( int n )
{
    displayDepth = n;
puts( "if > saveDepth, enlarge saveDepth, and fill with blanks" );
}

void
sliceSeq::setSaveDepth( int n )
{
    saveDepth = n;
puts( "if < displayDepth, shrink displayDepth, and free unused" );
}

//
// shift all slices down
//
void
sliceSeq::shift()
{
puts( "shift all slices down: delete last one and shift" );
}

//
// insert new slice
//
void
sliceSeq::insertSlice( float o1, float o2 )
{
printf( "compute new slice @ %g, %g\n", o1, o2 );
}

