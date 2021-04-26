#ifndef	_weight_h_
#define	_weight_h_

//
//  define an abstract Weight class that can change the weight based
//	on location (absolute or relative), or history, etc.
//

#include	<string>
#include	<vector>

#include "Dimensions.h"

// class Dimensions;
class Index;
class IndexArray;

class	Weight 
	{
	protected:
		Dimensions m_dims;
		double	m_constWgt;

	public:
		Weight(Dimensions const& dims, double val = 1.0)
			: m_dims(dims)
			, m_constWgt(val)
			{}

		virtual	~Weight();

		Dimensions const& dims() { return m_dims; }

		virtual std::string name();

		virtual	void init( /* Dimensions const& dims */ );

		virtual	void	getWgts(Index const& position,
								IndexArray const& relPositions,
								std::vector<double>& weights);
	}; // class Weight

#endif	/* _weight_h_ */

