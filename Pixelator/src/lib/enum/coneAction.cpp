//
//   Enumerate the pixels in an image away based on different rules, and
//   different seed points
//

#include	"coneAction.h"
#include	<math.h>
#include	<assert.h>

using namespace std;

//
//  precompute indexes of a cone, using 8-fold symetry
//
void ConeAction::init(// Dimensions const& dims // dimensions
					 )
	{
	Action::init(/* dims */);

	if(numDimensions() == 3)
		{
		printf( "3D cone (sphere) not implemented\n" );
		return;
		}
	}


string ConeAction::name()
	{
	return string("ConeAction");
	}


//
// Initialize neighbor data for the ConeAction class
//
void ConeAction::makeNbors()
	{
	Index index(numDimensions());

	m_nbors.clear();
	m_relNborWgts.clear();

	for( int y=0; y<=m_radius; y++ ) 
		{
		for( int x=0; x<=m_radius; x++ ) 
			{

			// compute distance from center
			float 	dist = sqrt(float(x*x + y*y));

			// compute linear ramp of weight from max at center 
			//	to 0 outside m_radius
			// RFE: this could be any exponent of distance
			float	w = 1.0 - dist/float(m_radius);
			if( w < 0.0 ) 
				continue;

			//
			//  now use 4-fold symetry to set other values
			//

			// XXX why skip center cell?
			// skip this cell
			if( x == 0 && y == 0 )
				continue;				

			// 1st quad
			index.set(+x, +y);
			m_nbors.push_back(index);
			m_relNborWgts.push_back(w);

			if( y != 0 ) 
				{
				// 4th quad
				index.set(+x, -y);
				m_nbors.push_back(index);
				m_relNborWgts.push_back(w);
				}
			if( x != 0 ) 
				{
				// 2nd quad
				index.set(-x, +y);
				m_nbors.push_back(index);
				m_relNborWgts.push_back(w);
				}
			if( x != 0 && y != 0 ) 
				{
				// 3rd quad
				index.set(-x, -y);
				m_nbors.push_back(index);
				m_relNborWgts.push_back(w);
				}
			}
		}
	setNumNbors(m_nbors.size());
	}



