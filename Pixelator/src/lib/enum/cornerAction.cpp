//
//   Enumerate the pixels in an image away based on different rules, and
//   different seed points
//

#include	"cornerAction.h"


using namespace std;

string CornerAction::name()
	{
	return string("CornerAction");
	}


//
// Initialize neighbor data for the CornerAction class
//
void CornerAction::makeNbors()
    {
	Index index(numDimensions());

    m_nbors.clear();
    index.set(-1, -1);	m_nbors.push_back(index);
    index.set(+1, -1);	m_nbors.push_back(index);
    index.set(-1, +1);	m_nbors.push_back(index);
    index.set(+1, +1);	m_nbors.push_back(index);

    setNumNbors(m_nbors.size());
    setConstWgts(); // XXX dependent on order, should use flag
    }




