#ifndef _Colormap_h_
#define _Colormap_h_

#include	<QColor>
#include	<QMap>

//
// A flexible colormap definition and interpolation of color
//
class Colormap
	{
	public:
		// Constructors
		Colormap();

		// Standard Colormap names
		enum ColormapName
			{
			Rainbow, // red-yellow-green-cyan-blue-magenta rainbow
			OneValTest, // one value in the middle test
			TwoValTest, // two values in the middle test
			};
		Colormap(ColormapName name);

		// Access operations
		bool hasAlpha() { return m_hasAlpha; }

		// Definition operations
		void addColor(float index, QColor color);

		// Lookup operations
		QColor lookup(float index); // index = [0,1]

	protected:
		struct IndexColor
			{
			float	m_index;
			QColor	m_color;
			}; // IndexColor

	private:
		typedef QMap<float, QColor>	MapFloatToColor;
		typedef MapFloatToColor::iterator MapFloatToColorIter;
		
		MapFloatToColor	m_colorMap;
		bool 			m_hasAlpha; // at least one color with some transparency

		// Color Interpolation Operations
		QColor interpColor(float v, float val0, QColor col0, float val1, QColor col1);
	}; // Colormap

#endif // _Colormap_h_
