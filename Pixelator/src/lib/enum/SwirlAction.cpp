//
//   Enumerate the pixels in an image away based on different rules, and
//   different seed points
//

#include	"SwirlAction.h"
#include	<math.h>

using namespace std;

string SwirlAction::name()
	{
	return string("SwirlAction");
	}


//
//  precompute indexes of a dir Action, using 8-fold symetry
//
void SwirlAction::init(// Dimensions const& dims // dimensions
					)
	{
	DirAction::init();

	// compute a table to index rotation of indexes
	for(int iX=0; iX<3; ++iX)
		{
		int x = iX-1;
		for(int iY=0; iY<3; ++iY)
			{
			int y = iY-1;
			if(-1 == x && -1 == y) { m_rotX[iX][iY] =  0;  m_rotY[iX][iY] = -1; }
			if( 0 == x && -1 == y) { m_rotX[iX][iY] = +1;  m_rotY[iX][iY] = -1; }
			if(+1 == x && -1 == y) { m_rotX[iX][iY] = +1;  m_rotY[iX][iY] =  0; }
			if(+1 == x &&  0 == y) { m_rotX[iX][iY] = +1;  m_rotY[iX][iY] = +1; }
			if(+1 == x && +1 == y) { m_rotX[iX][iY] =  0;  m_rotY[iX][iY] = +1; }
			if( 0 == x && +1 == y) { m_rotX[iX][iY] = -1;  m_rotY[iX][iY] = +1; }
			if(-1 == x && +1 == y) { m_rotX[iX][iY] = -1;  m_rotY[iX][iY] =  0; }
			if(-1 == x &&  0 == y) { m_rotX[iX][iY] = -1;  m_rotY[iX][iY] = -1; }
			}
		}
	}


//
//  move index by relative values in inds, and add weight to each one
//
void SwirlAction::doAction( CellArray *cells, Index const& index )
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
		// (and then rotated 1 cell CCW)
		//	regardless of state
		//
		int iX = -maxInd[X]+1;
		int iY = -maxInd[Y]+1;
		Index rel(m_dims);
		rel.set(m_rotX[iX][iY], m_rotY[iX][iY]);

		IndexArray indexes(m_dims);
		indexes.push_back(rel);

		std::vector<double>	primWgt(indexes.size());
		m_primary->getWgts(index, indexes, primWgt);
		cells->opPos(cfAdd, index, indexes, primWgt);
		}
    }




