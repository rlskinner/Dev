//
//   Enumerate the pixels in an image away based on different rules, and
//   different seed points
//

#include	<stdio.h>
#include	<stdlib.h>
#include	<unistd.h>

#include	"TextOutput.h"

#include	"diskSeed.h"
#include	"edgeSeed.h"
#include	"lineSeed.h"

#include	"coneAction.h"
#include	"contourAction.h"
#include	"cornerAction.h"
#include	"crossAction.h"
#include	"dirAction.h"
#include	"nborAction.h"
#include	"ringAction.h"

// void
// TextOutput::processEvent( int block ) 
// 	{
// 	m_cells->print();
// 
// 	while( block ) 
// 		{
// 		sleep( 1 );
// 		}
// 	}


// define all the test cases
enum TestCase
    {
    // test each seed class with the nborAction(4) Action
    cCenterPtNbor4,
    cLineNbor4,
    cEdgeNbor4,
    cDiskNbor4,

    // test each action class with a center point seed
    cNbor8CenterPt,
    cConeCenterPt,
    //     cContourCenterPt, // not sure what contourAction is supposed
    cCornerCenterPt,
    cCrossCenterPt,
    cDirCenterPt,
    cRingCenterPt,

    cNumTestCases // must be last
    };

void
setupTestCase(Dimensions const& dims, TestCase testCase, TextOutput *textOut)
    {
    switch(testCase)
	{
	case cCenterPtNbor4:
	    textOut->addSeed(new LineSeed(0.5, 0.5, 0.5, 0.5, new Weight(dims, 1.0)));
	    textOut->addAction(new NborAction(new Weight(dims, 1.0), 4));
	    break;

	case cLineNbor4:
	    textOut->addSeed(new LineSeed(0.25, 0.5, 0.75, 0.75, new Weight(dims, 1.0)));
	    textOut->addAction(new NborAction(new Weight(dims, 1.0), 4));
	    break;

	case cEdgeNbor4:
	    textOut->addSeed(new EdgeSeed(new Weight(dims, 1.0)));
	    textOut->addAction(new NborAction(new Weight(dims, 1.0), 4));
	    break;

	case cDiskNbor4:
	    textOut->addSeed(new DiskSeed(4, 4, 2, new Weight(dims, 1.0)));
	    textOut->addAction(new NborAction(new Weight(dims, 1.0), 4));
	    break;

	case cNbor8CenterPt:
	    textOut->addSeed(new LineSeed(0.5, 0.5, 0.5, 0.5, new Weight(dims, 1.0)));
	    textOut->addAction(new NborAction(new Weight(dims, 1.0), 8));
	    break;

	case cConeCenterPt:
	    textOut->addSeed(new LineSeed(0.5, 0.5, 0.5, 0.5, new Weight(dims, 1.0)));
	    textOut->addAction(new ConeAction(new Weight(dims, 1.0), 3));
	    break;

#if	0
	case cContourCenterPt:
	    textOut->addSeed(new LineSeed(0.5, 0.5, 0.5, 0.5, new Weight(dims, 1.0)));
	    textOut->addAction(new ContourAction(new Weight(dims, 3.0), new Weight(dims, 1.0)));
	    break;
#endif

	case cCornerCenterPt:
	    textOut->addSeed(new LineSeed(0.5, 0.5, 0.5, 0.5, new Weight(dims, 1.0)));
	    textOut->addAction(new CornerAction(new Weight(dims, 1.0)));
	    break;

	case cCrossCenterPt:
	    textOut->addSeed(new LineSeed(0.5, 0.5, 0.5, 0.5, new Weight(dims, 1.0)));
	    textOut->addAction(new CrossAction(new Weight(dims, 1.0), 3));
	    break;

	case cDirCenterPt:
	    textOut->addSeed(new LineSeed(0.5, 0.5, 0.5, 0.5, new Weight(dims, 1.0)));
	    textOut->addAction(new DirAction(new Weight(dims, 3.0), new Weight(dims, 1.0)));
	    break;

	case cRingCenterPt:
	    textOut->addSeed(new LineSeed(0.5, 0.5, 0.5, 0.5, new Weight(dims, 1.0)));
	    textOut->addAction(new RingAction(new Weight(dims, 1.0), 3));
	    break;

	default:
	    printf("\n\n*** Unimplemented test case: %d ***\n\n", testCase);
	    exit(1);
	}

    }


void
doTestCase(TestCase testCase)
	{
	const int cNumIters = 10;

	Dimensions dims(10, 10);

	CellArray *textCells = new CellArray(dims);
	TextOutput *textOut = new TextOutput;
	setupTestCase(dims, testCase, textOut);
    textOut->init(textCells);

	// XXX need names....
	printf("Test case %d  =========================\n", testCase);
	printf("Seeds:\n");
	textCells->print();
	printf("\n");

	Index index(2);
	for(int i=0; i<cNumIters; i++)
		{
		printf("iteration %d\n", i);
		textOut->pick(index);	// do one iteration
		textCells->print();
		printf("\n");
		}

	printf("End test case %d  =========================\n\n", testCase);
	delete textOut;
	}


    int
main( int /* argc */, char * /* argv */[] )
    {
    for(int i=0; i<cNumTestCases; ++i)
	{
	doTestCase(TestCase(i));
	}
    }
