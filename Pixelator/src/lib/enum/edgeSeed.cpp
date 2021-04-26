//
//   Enumerate the pixels in an image away based on different rules, and
//   different seed points
//

#include	"CellArray.h"
#include	"edgeSeed.h"

using namespace std;

string EdgeSeed::name()
	{
	return string("EdgeSeed");
	}


//
// Seed the CellArray along the edge
//
//  XXX doesn't use correct relative weight coordinates
//
void EdgeSeed::seedArray(CellArray *cells, // CellArray to seed
						 Dimensions const& dims
						 )
    {
	IndexArray indexes(dims);	

	Index index(2);
	for(int i=0; i<dims.size(X); ++i)
		{
		index.set(i, 0);
		indexes.push_back(index);
		index.set(i, int(dims.size(Y)-1));
		indexes.push_back(index);
		}

	for(int i=1; i<dims.size(Y)-1; ++i)
		{
		index.set(0, i);
		indexes.push_back(index);
		index.set(int(dims.size(X)-1), i);
		indexes.push_back(index);
		}

	Index origin(dims);
	origin.set(0); // XXX should zero be the default value?
	std::vector<double> weights(indexes.size());
	m_wgt->getWgts(origin, indexes, weights);
	cells->opPos(cfAdd, origin, indexes, weights);
    }



