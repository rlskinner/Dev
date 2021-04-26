#include	<GL/gl.h>
#include	<GL/glut.h>
#include	<stdio.h>
#include	<stdlib.h>
#include	<unistd.h>
#include	<math.h>
#include	<sys/types.h>

#include	<octSeq.h>

// #include	<il/ilMemoryImg.h>
// #include	<il/ilConstImg.h>

#include	"torus.h"

//
//  independent variables the user can set
//
int	attractorSize = 256;
int	numAttractors = 2;
int	subdivAttractor = 1;
float	omegaWindowSize = .001;
float	omega[2] = { 0.6, 0.3 };	// { .1234567, .3456789 };
// (and omega1, omega2)

// ilMemoryImg	*attractorCells;
// ilMemoryImg	*windowPixels;
uchar_t	*attractorCells;
uchar_t	*windowPixels;

//
//  Menu identifiers for the variables above
//
int	attrSizeMenuID;
int	numAttractorsMenuID;
int	subdivAttractorMenuID;

//  dependent variables
int	windowSize = attractorSize*numAttractors;

//
// info about the tiling operations
//
int	numTiles;
int	tilesDone;
int	interruptTiling = GL_FALSE;
short	*octSequence;

int
intLog2( int v )
{
    return int( rint( log(v)/log(2.0) ) );
}


void
replicateTile( int Ai, int Aj, int rep )
{
//     for( int j=0; j<rep; j++ ) {
// 	for( int i=0; i<rep; i++ ) {
// 	    windowPixels->copyTile( Ai+i*attractorSize, Aj+j*attractorSize, 
// 	    	attractorSize, attractorSize, attractorCells, 0, 0 );
// 	}
//     }
//     windowPixels->markDirty();
    for( int j=0; j<rep; j++ ) {
	for( int i=0; i<rep; i++ ) {
	    for( int h=0; h<attractorSize; h++ ) {
		memcpy( windowPixels+
			(Aj+j*attractorSize+h)*windowSize
			+(Ai+i*attractorSize), 
			attractorCells+h*attractorSize, attractorSize );
	    }
	}
    }
}

void
subsetTile( int Ai, int Aj, int Aoff_i, int Aoff_j, int size )
{
//     windowPixels->copyTile( Ai+Aoff_i, Aj+Aoff_j, size, size, 
// 	    attractorCells, Aoff_i, Aoff_j, );
//     windowPixels->markDirty();
    int Wi = Ai+Aoff_i;
    int Asubi = Aoff_i;

    for( int j=0; j<size; j++ ) {
	int Wj = Aj+Aoff_j+j;
	int Asubj = Aoff_j+j;
	memcpy( windowPixels+Wj*windowSize+Wi,
	    attractorCells+Asubj*attractorSize+Asubi, size );
    }
}

inline	int	facetsOnSide() { return numAttractors*subdivAttractor; }
inline	int	facetSize() { return windowSize/facetsOnSide(); }

void
doTile( int i, int j, int size )
{
// printf( "doTile( %d, %d, %d )\n", i, j, size );

    // find omega values
    float Ox = omega[0] - omegaWindowSize/2.0 
    		+ i*omegaWindowSize/facetsOnSide();
    float Oy = omega[1] - omegaWindowSize/2.0 
    		+ j*omegaWindowSize/facetsOnSide();

    // compute the attractor
    omega1 = Ox;
    omega2 = Oy;
//     makeMap( (uchar_t*)attractorCells->getDataPtr(), attractorSize, 255 );
    memset( attractorCells, 0, attractorSize*attractorSize );
    makeMap( attractorCells, attractorSize, 255 );

    // find position of the attractor in window coordinates
    int Ai = attractorSize*((i*facetSize())/attractorSize);
    int Aj = attractorSize*((j*facetSize())/attractorSize);

    // find out if we replicate the tile, or grab a subset
    //	the replication factor is (size/subdivAttractor)
    if( size >= subdivAttractor ) {
	// replicate
	printf( "A[%d,%d] x %d :: omega = (%g, %g)\n", 
		Ai, Aj, size/subdivAttractor, Ox, Oy );
	replicateTile( Ai, Aj, size/subdivAttractor );
    } else {
	// subset
	int Aoff_i = (i*windowSize/facetsOnSide()) - Ai;
	int Aoff_j = (j*windowSize/facetsOnSide()) - Aj;
	printf( "A[%d,%d] @ [%d,%d], %d pixels :: omega = (%g, %g)\n", 
		Ai, Aj, Aoff_i, Aoff_j, (attractorSize*size)/subdivAttractor, 
		Ox, Oy );
	subsetTile( Ai, Aj, Aoff_i, Aoff_j, (attractorSize*size)/subdivAttractor );
    }
    glutPostRedisplay();
}


void
tileIdleCB()
{
    if( tilesDone >= numTiles || interruptTiling ) {
	glutIdleFunc( NULL );
	return;
    }

    doTile( octSequence[3*tilesDone+0], octSequence[3*tilesDone+1], 
    	octSequence[3*tilesDone+2] );
    tilesDone++;
}

void
doTiling()
{
    numTiles = numAttractors*subdivAttractor;
    numTiles *= numTiles;

    //  cache the tiling parameters, so we can determine whether 
    //	we can continue from the last tile
    static	int	firstTime = GL_TRUE;
    static	int	continueTiling = GL_FALSE;
    static	float	_omega[2];
    static	int	_attractorSize;
    static	int     _numAttractors;
    static	int     _subdivAttractor;
    static	int     _omegaWindowSize;

    if( !firstTime ) {
	continueTiling = (_omega[0] == omega[0]) 
		       && (_omega[1] == _omega[1])
		       && (_attractorSize == attractorSize)
		       && (_numAttractors == numAttractors)
		       && (_subdivAttractor == subdivAttractor)
		       && (_omegaWindowSize == omegaWindowSize);
    }

    _omega[0] = omega[0];
    _omega[1] = _omega[1];
    _attractorSize = attractorSize;
    _numAttractors = numAttractors;
    _subdivAttractor = subdivAttractor;
    _omegaWindowSize = omegaWindowSize;;
    firstTime = GL_FALSE;

    if( !continueTiling ) {
	tilesDone = 0;
	delete octSequence;
	octSequence = octSeq( intLog2(numAttractors*subdivAttractor) );
    }
    interruptTiling = GL_FALSE;

//    windowPixels->qFillTile3D( NULL, 0, 0, 0, windowSize, windowSize, 1, &value );
    memset( windowPixels, 0, windowSize*windowSize );

    glutIdleFunc( tileIdleCB );
}


void
redisplay()
{
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluOrtho2D( 0, windowSize, 0, windowSize );
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    glTranslatef( 0.375, 0.375, 0.375 );

    glRasterPos2i( 0, 0 );
//    void *data = windowPixels->getDataPtr();
//    glDrawPixels( windowSize, windowSize, GL_LUMINANCE, GL_UNSIGNED_BYTE, 
//    		windowPixels->getDataPtr() );
    glDrawPixels( windowSize, windowSize, GL_LUMINANCE, GL_UNSIGNED_BYTE, 
    		windowPixels );
}

void
keybdInput( unsigned char key, int, int )
{
    printf( "key = %c\n", key );
    switch( key ) {
	case 0x1b:
	    exit(0);
	    break;
    }
}

void
mouseCB( int button, int state, int x, int y )
{
    if( button != GLUT_LEFT_BUTTON ) return;
    if( state != GLUT_DOWN ) return;

    omega[0] = (float)x / (windowSize-1);
    omega[1] = 1.0 - (float)y / (windowSize-1);
    printf( "omega = { %g, %g }\n", omega[0], omega[1] );
}


enum	MainMenuAction {
	    StartTiling,
	    InterruptTiling,
};

//
//  menu callback
//
void
mainMenuCB( int menuID )
{
    switch( menuID ) {
	case StartTiling:
	    doTiling();
	    break;
	case InterruptTiling:
	    interruptTiling = GL_TRUE;
	    break;
	default:
	    printf( "unrecognized main menu action: %d\n", menuID );
	    break;
    }
}

void
setWindowSize()
{
    windowSize = attractorSize*numAttractors;
    if( windowSize > 1024 ) {
	printf( "new window size is %d pixels square,\n", windowSize );
	printf( "  are you sure you want that?\n" );
    }
    glutReshapeWindow( windowSize, windowSize );
    
    if( NULL == windowPixels ) {
//	windowPixels = new ilMemoryImg( iflSize(windowSize,windowSize), iflUChar );
	windowPixels = (uchar_t*)malloc( windowSize*windowSize*sizeof(uchar_t) );
    } else {
//	windowPixels->setSize( windowSize, windowSize );
	windowPixels = (uchar_t*)realloc( windowPixels, windowSize*windowSize*sizeof(uchar_t) );
    }

//    windowPixels->qFillTile3D( NULL, 0, 0, 0, windowSize, windowSize, 1, &value );
    memset( windowPixels, 0, windowSize*windowSize );
}

void
setAttractorSizeCB( int value )
{
    printf( "set attractor size = %d\n", value );
    attractorSize = value;
    setWindowSize();
    
    if( NULL == attractorCells ) {
// 	attractorCells = new ilMemoryImg( iflSize(value,value), iflUChar );
	attractorCells = (uchar_t*)malloc( attractorSize*attractorSize*sizeof(uchar_t) );
    } else {
// 	attractorCells->setSize( attractorSize, attractorSize );
	attractorCells = (uchar_t*)realloc( attractorCells, 
				attractorSize*attractorSize*sizeof(uchar_t) );
    }
}

void
setNumAttractorsCB( int value )
{
    printf( "set number of attractors = %d\n", value );
    numAttractors = value;
    setWindowSize();
}

void
subdivAttractorCB( int value )
{
    printf( "set attractors subdivision = %d\n", value );
    subdivAttractor = value;
}

float	epsilonTable[] = { .1, .2, .3, .4, .5, .6, .7, .8, .9, 1.0 };
void
setEpsilonCB( int index )
{
    setEpsilon( epsilonTable[index] );
}

void
initMenus()
{
    // attractor size submenu
    int	attractorSizeMenuID = glutCreateMenu( setAttractorSizeCB );
	glutAddMenuEntry( "16", 16 );
	glutAddMenuEntry( "32", 32 );
	glutAddMenuEntry( "64", 64 );
	glutAddMenuEntry( "128", 128 );
	glutAddMenuEntry( "256", 256 );
	glutAddMenuEntry( "512", 512 );
	glutAddMenuEntry( "1024", 1024 );

    // number of attractors submenu
    int numAttractorsMenuID = glutCreateMenu( setNumAttractorsCB );
	glutAddMenuEntry( "2", 2 );
	glutAddMenuEntry( "4", 4 );
	glutAddMenuEntry( "8", 8 );
	glutAddMenuEntry( "16", 16 );
	glutAddMenuEntry( "32", 32 );
	glutAddMenuEntry( "64", 64 );

    // subdivision of attractors
    int subdivAttractorMenuID = glutCreateMenu( subdivAttractorCB );
	glutAddMenuEntry( "1", 1 );
	glutAddMenuEntry( "2", 2 );
	glutAddMenuEntry( "4", 4 );
	glutAddMenuEntry( "8", 8 );
	glutAddMenuEntry( "16", 16 );
	glutAddMenuEntry( "32", 32 );
	glutAddMenuEntry( "64", 64 );

    // epsilon values
    int	setEpsilonMenuID = glutCreateMenu( setEpsilonCB );
    for( int i=0; i<sizeof(epsilonTable)/sizeof(epsilonTable[0]); i++ ) {
	char	buf[10];
	sprintf( buf, "%g", epsilonTable[i] );
	glutAddMenuEntry( buf, i );
    }

    // main menu
    attrSizeMenuID = glutCreateMenu( mainMenuCB );
    glutAddMenuEntry( "Start Tiling", StartTiling );
    glutAddMenuEntry( "Interrupt Tiling", InterruptTiling );
    glutAddSubMenu( "Attractor Size", attractorSizeMenuID );
    glutAddSubMenu( "Number of Attractors", numAttractorsMenuID );
    glutAddSubMenu( "Subdivide Attractors", subdivAttractorMenuID );
    glutAddSubMenu( "Set Epsilon", setEpsilonMenuID );

    glutAttachMenu( GLUT_RIGHT_BUTTON );
}

void
init()
{
    initMenus();
    setEpsilon( 0.5 );
}

void
main( int argc, char *argv[] )
{
    glutInit( &argc, argv );
    glutInitWindowSize( 512, 512 );
    glutCreateWindow( "Tiled Torus Attractor" );
    glutInitDisplayMode( GLUT_RGB | GLUT_SINGLE );
    glutDisplayFunc( redisplay );
    glutKeyboardFunc( keybdInput );
    glutMouseFunc( mouseCB );

    init();
    setAttractorSizeCB( attractorSize );
    glutMainLoop();
}
