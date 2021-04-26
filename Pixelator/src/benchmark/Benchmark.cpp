//
//  Benchmark every seed and action
//

#include	"PixelEnumerator.h"

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

#include	<QTime>

#include	<stdio.h>
#include	<stdlib.h>
#include	<unistd.h>
#include	<assert.h>

#include	<algorithm>
#include	<iostream>
#include	<sstream>
#include	<vector>

using namespace std;

// define Seed benchmarks
enum SeedBenchmarks
    {
    // test the seed onlhy, no actions
    cSeedCenter,
    cSeedLine,
    cSeedEdge,
    cSeedDisk,

    cNumSeedBenchmarks // must be last
	};


// define Action benchmarks
enum ActionBenchmarks
	{
    // test each action class with a point seed at the center
    cActionNbor4,
    cActionNbor8,
    cActionCone,
    cActionCorner,
    cActionCross,
    cActionDir,
    cActionRing,

    cNumActionBenchmarks // must be last
    };


void doSeedBenchmark(int iBenchmark, Dimensions const &dims)
	{
	CellArray *cells = new CellArray(dims, CellArray::cSavePickSequence);
	PixelEnumerator *bench = new PixelEnumerator;

	Seed *seed;

	QTime	timer;
	timer.start();
	switch(iBenchmark)
		{
		case cSeedCenter:
			seed = new LineSeed(0.5, 0.5, 0.5, 0.5, new Weight(dims, 1.0));
			break;

		case cSeedLine:
			seed = new LineSeed(0.0, 0.0, 1.0, 1.0, new Weight(dims, 1.0));
			break;

		case cSeedEdge:
			seed = new EdgeSeed(new Weight(dims, 1.0));
			break;

		case cSeedDisk:
			seed = new DiskSeed(dims[0]/2, dims[0]/2, dims[0]/2, new Weight(dims, 1.0));
			break;

		default:
			assert(false);
			break;
		}

	bench->addSeed(seed);
	bench->init(cells);

	int elapsedMsec = timer.elapsed();
	printf("%3.1f s\t: seed %s\n", elapsedMsec/1000.0, seed->name().c_str());
	fflush(stdout);

	delete cells;
	delete bench;
	}


void doActionBenchmark(int iBenchmark, Dimensions const &dims)
	{
	CellArray *cells = new CellArray(dims, CellArray::cSavePickSequence);
	PixelEnumerator *bench = new PixelEnumerator;
	bench->addSeed(new LineSeed(0.5, 0.5, 0.5, 0.5, new Weight(dims, 1.0)));

	Action *action;

	QTime	timer;
	timer.start();
	switch(iBenchmark)
		{
		case cActionNbor4:
			action = new NborAction(new Weight(dims, 1.0), 4);
			break;

		case cActionNbor8:
			action = new NborAction(new Weight(dims, 1.0), 8);
			break;

		case cActionCone:
			action = new ConeAction(new Weight(dims, 1.0), 3);
			break;

		case cActionCorner:
			action = new CornerAction(new Weight(dims, 1.0));
			break;

		case cActionCross:
			action = new CrossAction(new Weight(dims, 1.0), 3);
			break;

		case cActionDir:
			action = new DirAction(new Weight(dims, 3.0), new Weight(dims, 1.0));
			break;

		case cActionRing:
			action = new RingAction(new Weight(dims, 1.0), 3);
			break;

		default:
			assert(false);
			break;
		}

	bench->addAction(action);
	bench->init(cells);

	Index index(2);
	while(cells->numWaiting() > 0)
		{
		bench->pick(index);
		}

	int elapsedMsec = timer.elapsed();
	printf("%3.1f s\t: action %s\n", elapsedMsec/1000.0, action->name().c_str());
	fflush(stdout);

	delete cells;
	delete bench;
	}


void parseArgs(int argc,
			   char *argv[],
			   int *caseSize,
			   vector<int> *seedBenchmarks,
			   vector<int> *actionBenchmarks
			   )
	{
	bool allTestFlag = false;

	string progName(*argv);
	argc--;
	argv++;

	bool errorFlag = false;
	while(argc && !errorFlag)
		{
		string arg(*argv);
		argc--;
		argv++;

		if(arg.length() < 2)
			{
			errorFlag = true;
			continue;
			}

		if('-' == arg[0])
			{
			int value;
			string afterMinus(arg.substr(2));
			switch(arg[1])
				{
				case 'A':	
					allTestFlag = true;
					break;

				case 'S':	
					istringstream(afterMinus) >> *caseSize;
					if(*caseSize <= 0)
						{
						cerr << "-S cell array size must be a positive integer" << endl;
						exit(1);
						}
					break;

				case 'a':	
					istringstream(afterMinus) >> value;
					actionBenchmarks->push_back(value);
					break;

				case 's':	
					istringstream(afterMinus) >> value;
					seedBenchmarks->push_back(value);
					break;

				default:	
					errorFlag = true;
					break;
				}
			}
		else
			{
			errorFlag = true;
			}
		}

	if(errorFlag)
		{
		cerr << "usage: " << progName << " [-A] [-S size] [-s seed_test#]* [-a action_test#]*" << endl;
		cerr << "  A               : Run all tests" << endl;
		cerr << "  S size          : Cell array size" << endl;
		cerr << "  s seed_test#    : Run Seeed test #" << endl;
		cerr << "  a action_test#  : Run Action test #" << endl;
		exit(1);
		}


	// if -A flag given or no -a or -s flags, then execute all benchmarks
	if(allTestFlag || (seedBenchmarks->size() == 0 && actionBenchmarks->size() == 0))
		{
		for(int i=0; i<cNumSeedBenchmarks; ++i)

			seedBenchmarks->push_back(i);
		for(int i=0; i<cNumActionBenchmarks; ++i)

			actionBenchmarks->push_back(i);
		}

	// sort and remove duplicates
	vector<int>::iterator lastUnique;
	sort(seedBenchmarks->begin(), seedBenchmarks->end());
	lastUnique = unique(seedBenchmarks->begin(), seedBenchmarks->end());
	seedBenchmarks->erase(lastUnique, seedBenchmarks->end());
	sort(actionBenchmarks->begin(), actionBenchmarks->end());
	lastUnique = unique(actionBenchmarks->begin(), actionBenchmarks->end());
	actionBenchmarks->erase(lastUnique, actionBenchmarks->end());

	// Are all the benchmark #'s in the valid ranges? (all sorted)
	int id;
	if(seedBenchmarks->size() > 0)
		{
		id = seedBenchmarks->front();
		if(id < 0)
			{
			cerr << "invalid Seed benchmark ID: " << id << endl;
			exit(1);
			}

		id = seedBenchmarks->back();
		if(id >= cNumSeedBenchmarks)
			{
			cerr << "invalid Seed benchmark ID: " << id << ", max is " << cNumSeedBenchmarks-1 << endl;
			exit(1);
			}
		}

	if(actionBenchmarks->size() > 0)
		{
		id = actionBenchmarks->front();
		if(id < 0)
			{
			cerr << "invalid Action benchmark ID: " << id << endl;
			exit(1);
			}

		id = actionBenchmarks->back();
		if(id >= cNumActionBenchmarks)
			{
			cerr << "invalid Action benchmark ID: " << id << ", max is " << cNumActionBenchmarks-1 << endl;
			exit(1);
			}
		}

	}


int main( int argc, char *argv[] )
	{
	int caseSize = 50; // how large is the cell array?
	vector<int> seedBenchmarks;
	vector<int> actionBenchmarks;

	parseArgs(argc, argv, &caseSize, &seedBenchmarks, &actionBenchmarks);

	QTime timer;
	timer.start();

	Dimensions benchDims(caseSize, caseSize);
	int numBenchmarks = 0;
	vector<int>::iterator it;
	for(it = seedBenchmarks.begin(); it != seedBenchmarks.end(); ++it)
		{
		doSeedBenchmark(*it, benchDims);
		numBenchmarks++;
		}

	for(it = actionBenchmarks.begin(); it != actionBenchmarks.end(); ++it)
		{
		doActionBenchmark(*it, benchDims);
		numBenchmarks++;
		}

	if(numBenchmarks > 1)
		{
		printf("------------------------------\n");
		int elapsedMsec = timer.elapsed();
		printf("%3.1f s\t: total time\n", elapsedMsec/1000.0);
		qDebug("%3.1f s\t: total time\n", elapsedMsec/1000.0);
		}
	}
