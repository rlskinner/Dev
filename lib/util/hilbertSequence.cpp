//
//  generate and return a Hilbert sequence
//

#include	<stdio.h>
#include	<hilbertSequence.h>

HilbertSequence::HilbertSequence( int res )
{
    points = NULL;
    allocedPoints = 0;
    setResolution( res );
}

HilbertSequence::~HilbertSequence()
{
    delete points;
}

void
HilbertSequence::setResolution( int res )
{
    if( res >= 1 ) {
	resolution = res;
	numberPoints = 1 << (2*resolution);
	reallocPoints();
    } else {
	fprintf( stderr, "HilbertSequence::setResolution:  "
			 "invalid resolution:  %d\n", res );
    }
}

int
HilbertSequence::getSequence( HilbertPoint **seq )
{
    *seq = points;
    return numberPoints;
}

void
HilbertSequence::computeSequence()
{
    angle = 0;
    currentI = currentJ = 0;
    currentPoint = 0;
    setPoint();
    hilbert( +1, resolution );
}

void
HilbertSequence::hilbert( int orient, int level )
{
	if( level-- <= 0 ) 
		return;

	angle += orient * 90;
	hilbert( -orient, level );
	step();

	angle -= orient * 90;
	hilbert( orient, level );
	step();

	hilbert( orient, level );
	angle -= orient * 90;
	step();

	hilbert( -orient, level );
	angle += orient * 90;
}

void
HilbertSequence::step()
{
	while( angle < 0 ) 
		angle += 360;

	while( angle > 270 )
		angle -= 360;

	if( angle == 0 ) {
		currentI++;
	}
	else if( angle == 90 ) {
		currentJ++;
	}
	else if( angle == 180 ) {
		currentI--;
	}
	else if( angle == 270 ) {
		currentJ--;
	}
	
	setPoint();
}

void
HilbertSequence::setPoint()
{
	points[currentPoint].i = currentI;
	points[currentPoint].j = currentJ;
	currentPoint++;
}

void
HilbertSequence::reallocPoints()
{
    if( points != NULL ) {
	if( numberPoints > allocedPoints ) {
	    delete points;
	    points = new HilbertPoint[numberPoints];
	    allocedPoints = numberPoints;
	}
    } else {
	points = new HilbertPoint[numberPoints];
	allocedPoints = numberPoints;
    }
}



#ifdef	TEST
void
printSequence( HilbertSequence &hs )
{
    int	n;
    HilbertPoint	*seq;

    hs.computeSequence();
    n = hs.getSequence( &seq );
    for( int i=0; i<n; i++ ) {
	printf( "seq[%5d] = (%5d, %5d)\n", i, seq[i].i, seq[i].j );
    }
}

void
main()
{
    HilbertSequence	hs( 2 );
    printSequence( hs );
    
    hs.setResolution( 4 );
    printSequence( hs );

    hs.setResolution( 3 );
    printSequence( hs );
}
#endif
