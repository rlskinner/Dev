#ifndef	_SwirlAction_
#define	_SwirlAction_

#include	"dirAction.h"

class	SwirlAction : public DirAction 
	{
	protected:
		int		m_rotX[3][3];
		int		m_rotY[3][3];

	public:
		SwirlAction( Weight *_primary, Weight *_wgt )
			: DirAction( _primary, _wgt )
			{ }

		virtual std::string name();

		virtual	void	init(/* Dimensions const& dims */);
		virtual void	doAction( CellArray *cells, Index const& index);
	};
	
#endif	/* _SwirlAction_ */

