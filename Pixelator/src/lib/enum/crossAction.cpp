//
//   Enumerate the pixels in an image away based on different rules, and
//   different seed points
//

#include	"crossAction.h"
#include	<math.h>
#include	<assert.h>

using namespace std;

string CrossAction::name()
	{
	return string("CrossAction");
	}


//
//  precompute indexes of a cross, using 4-fold symetry
//
void CrossAction::init(// Dimensions const& dims // dimensions
					  )
    {
    Action::init(/* dims */);

    if(numDimensions() == 3)
	{
	printf( "3D cross (sphere) not implemented\n" );
	return;
	}
    }


//
// Initialize neighbor data for the CrossAction class
//
void CrossAction::makeNbors()
	{
	m_nbors.clear();

	Index index(numDimensions());
	for(int i=1; i<=m_size; i++) 
		{

		// compute linear ramp of weight from max at center 
		//	to 0 outside radius
		// RFE: this could be any exponent of distance
		float	w = 1.0 - i/float(m_size);
		if( w < 0.0 )
			continue;

		//
		//  now use 4-fold symetry to set other values
		//
		// right
		index.set(+i, +0);
		m_nbors.push_back(index);
		m_relNborWgts.push_back(w);

		// left
		index.set(-i, +0);
		m_nbors.push_back(index);
		m_relNborWgts.push_back(w);

		// up
		index.set(+0, +i);
		m_nbors.push_back(index);
		m_relNborWgts.push_back(w);

		// down
		index.set(+0, -i);
		m_nbors.push_back(index);
		m_relNborWgts.push_back(w);
		}

	setNumNbors(m_nbors.size());
	}




