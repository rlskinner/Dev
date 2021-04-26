#ifndef	_crossAction_
#define	_crossAction_

#include	"action.h"

class	CrossAction : public Action 
	{
	protected:
		int	m_size;

		virtual	void	makeNbors();

	public:
		CrossAction( Weight *wgt, int sz )
			: Action( wgt )
			{
			m_size = sz; 
			}

		virtual std::string name();

		virtual	void	init(/* Dimensions const& dims */);
	};
	
#endif	/* _CrossAction_ */

