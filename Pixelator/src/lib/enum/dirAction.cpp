//
//   Enumerate the pixels in an image away based on different rules, and
//   different seed points
//

#include	"dirAction.h"
#include	<math.h>

using namespace std;

string DirAction::name()
	{
	return string("DirAction");
	}


//
//  precompute indexes of a dir Action, using 8-fold symetry
//
void DirAction::init(// Dimensions const& dims // dimensions
					)
	{
	Action::init(/* dims */);
	m_primary->init(/* dims */);

	if(numDimensions() == 3) 
		{
		printf( "3D dir not implemented\n" );
		return;
		}
	}


//
// Initialize neighbor data for the DirAction class
//
void DirAction::makeNbors()
	{
	Index index(m_dims);
	for(int x=-1; x<=1; x++) 
		{
		for(int y=-1; y<=1; y++) 
			{
			if(x == 0 && y == 0) 
				continue;

			index.set(x, y);
			m_nbors.push_back(index);
			}
		}

	setNumNbors(m_nbors.size());
	setConstWgts();		//  we don't have relative cell weights // XXX dependent on order, should use flag
	}

//
//  move index by relative values in inds, and add weight to each one
//
void DirAction::doAction( CellArray *cells, Index const& index )
    {
    //
    //	Add the default weight to all empty neighbor cells:
    //  	the default action rule does the right thing, if the 
    //		selection state is empty
    //
    Action::doAction( cells, index );

    Index maxInd(numDimensions());
    if(findLastNborPicked(maxInd))
		{
		//
		// add bigWgt to cell OPPOSITE last one picked
		//	regardless of state
		//
		Index rel(m_dims);
		rel.set(-maxInd[X], -maxInd[Y]);
		IndexArray indexes(m_dims);
		indexes.push_back(rel);

		std::vector<double>	primWgt(indexes.size());
		m_primary->getWgts(index, indexes, primWgt);
		cells->opPos(cfAdd, index, indexes, primWgt);
		}
    }




