#include	"weight.h"

#include	"Dimensions.h"
#include	"Index.h"

#include	<assert.h>

using namespace std;

//
//  define an abstract weight class that can change the weight based
//	on location (absolute or relative), or history, etc.
//

Weight::~Weight()
	{
	}


string Weight::name()
	{
	return string("Weight");
	}


// 
// Initialize the Weight class from the cell array dimensions
//
void Weight::init(// Dimensions const& dims // dimensions
				 )
	{
	}


//
// Get an array of weights for the given array of indexes
// 		Weight returns a constant weight
//
void Weight::getWgts(Index const& position, // index of cell to get weights for
					 IndexArray const& relPositions, // indexes relative to position
					 std::vector<double>& weights // out: weights [n]
					)
	{
	assert(weights.size() <= relPositions.size());

	weights.resize(relPositions.size());
	fill(weights.begin(), weights.end(), m_constWgt);
	}


