//
//   Enumerate the pixels in an image away based on different rules, and
//   different seed points
//

#include	"nborAction.h"

using namespace std;

NborAction::NborAction(Weight *wgt, int connect )
    : Action( wgt )
    {
    m_connectedness = connect;
    }


string NborAction::name()
	{
	return string("NborAction");
	}


//
// Initialize neighbor data for the 4 or 8-connected NborAction class
//
void NborAction::makeNbors()
	{
	m_nbors.resize(0);

	Index	nb(2);
	if( m_connectedness == 8 ) 
		{
		nb[0] = -1;	nb[1] = -1; m_nbors.push_back(nb);
		nb[0] = +1;	nb[1] = +1; m_nbors.push_back(nb);
		nb[0] = +1;	nb[1] = -1; m_nbors.push_back(nb);
		nb[0] = -1;	nb[1] = +1; m_nbors.push_back(nb);
		}

	nb[0] = -1;	nb[1] =  0; m_nbors.push_back(nb);
	nb[0] = +1;	nb[1] =  0; m_nbors.push_back(nb);
	nb[0] =  0;	nb[1] = -1; m_nbors.push_back(nb);
	nb[0] =  0;	nb[1] = +1; m_nbors.push_back(nb);

	setNumNbors(m_nbors.size());
	setConstWgts(); // XXX dependent on order, should use flag
	}




