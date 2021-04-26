//
//   seed the cells with a disk of constant relative weight
//

#include	<math.h>

#include	"cellArray.h"
#include	"diskSeed.h"

using namespace std;

//
// Create a Seed shaped like a disk.
//
DiskSeed::DiskSeed(int _cx, // center of the disk in pixels (need relative?)
				   int _cy,
				   int _rad, // radius of disk in pixels (need relative?)
				   Weight *wgt // input weight
				   )
	: Seed( wgt )
	{
	m_cx = _cx;
	m_cy = _cy;
	m_radius = _rad;
	if( m_radius <= 0 )
		m_radius = 1;
	}


string DiskSeed::name()
	{
	return string("DiskSeed");
	}


// 
// Seed the CellArray with a disk
//
void DiskSeed::seedArray(CellArray *cells, // CellArray to seed
						 Dimensions const& dims
						)
	{
	IndexArray indexes(dims);

	Index index(2);
	for( int y=0; y<=m_radius; y++ ) 
		{
		for( int x=0; x<=m_radius; x++ ) 
			{
			//
			//  see if we are inside disk
			//
			if( x*x + y*y > m_radius*m_radius )
				continue;

			//
			//  now use 4-fold symetry to set other values
			//
			// 1st quad
			index.set(+x, +y);
			indexes.push_back(index);

			// 4th quad
			if( y != 0 ) 
				{
				index.set(+x, -y);
				indexes.push_back(index);
				}

			// 2nd quad
			if( x != 0 ) 
				{
				index.set(-x, +y);
				indexes.push_back(index);
				}

			// 3rd quad
			if( x != 0 && y != 0 ) 
				{
				index.set(-x, -y);
				indexes.push_back(index);
				}
			}
		}

	std::vector<double>	weights(indexes.size());
	Index	origin(2);
	origin.set(m_cx, m_cy);
	m_wgt->getWgts(origin, indexes, weights);
	cells->opPos(cfAdd, origin, indexes, weights);
	}


