#ifndef	_coneAction_
#define	_coneAction_

#include	"action.h"

class	ConeAction : public Action 
	{
	int	m_radius;

	virtual	void	makeNbors();

	public:
		ConeAction( Weight *wgt, int rad )
			: Action( wgt )
			{ m_radius = rad; }

		virtual std::string name();

		virtual	void	init(/* Dimensions const& dims */);
	};
	
#endif	/* _ConeAction_ */

