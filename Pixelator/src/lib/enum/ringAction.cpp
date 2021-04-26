//
//   Enumerate the pixels in an image away based on different rules, and
//   different seed points
//

#include	"RingAction.h"
#include	<math.h>
#include	<assert.h>

using namespace std;

RingAction::RingAction( Weight *_wgt, int rad )
    : Action( _wgt )
    {
    m_radius = rad;
    }


string RingAction::name()
	{
	return string("RingAction");
	}


// 
// Initialize the RingAction from the cell array dimensions
//
void RingAction::init(// Dimensions const& dims // dimensions
					 )
	{
	Action::init(/* dims */);

	if(numDimensions() == 3) 
		{
		printf( "3D ring (sphere) not implemented\n" );
		return;
		}
	}



//
// Initialize neighbor data for the RingAction class
//  -- precompute indexes of a ring, using 8-fold symetry
//
void RingAction::makeNbors()
	{
	m_nbors.resize(0);

	Index index(numDimensions());
	for( int y=0; y<m_radius; y++ ) 
		{
		int	x = roundToInt(sqrt(double(m_radius*m_radius-y*y)));
		if( y <= x ) 
			{// only do first octant, then fold
			index[X] = +x;
			index[Y] = +y;
			m_nbors.push_back(index);
			if( y != 0 ) 
				{
				index[X] = +x;	// 8th octant
				index[Y] = -y;
				m_nbors.push_back(index);
				}
			if( x != 0 ) 
				{
				index[X] = -x;	// 4rd octant
				index[Y] = +y;
				m_nbors.push_back(index);
				}
			if( x != 0 && y != 0 ) 
				{
				index[X] = -x;	// 5th octant
				index[Y] = -y;
				m_nbors.push_back(index);
				}

			if( y == x ) continue;

			index[X] = +y;	// 2nd octant
			index[Y] = +x;
			m_nbors.push_back(index);
			if( x != 0 ) 
				{
				index[X] = +y;	// 3th octant
				index[Y] = -x;
				m_nbors.push_back(index);
				}
			if( y != 0 ) 
				{
				index[X] = -y;	// 6rd octant
				index[Y] = +x;
				m_nbors.push_back(index);
				}
			if( x != 0 && y != 0 ) 
				{
				index[X] = -y;	// 7th octant
				index[Y] = -x;
				m_nbors.push_back(index);
				}
			}
		}

	setNumNbors( 8*m_radius );	// overestimate number of indexes
	setConstWgts(); // XXX dependent on order, should use flag
	}




