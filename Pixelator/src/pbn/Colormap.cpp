#include	<QtAlgorithms>

#include	"Colormap.h"

Colormap::Colormap()
	: m_colorMap()
	, m_hasAlpha(false)
	{
	}


Colormap::Colormap(ColormapName name)
	: m_colorMap()
	, m_hasAlpha(false)
	{
	switch(name)
		{
		default:
			// XXX assert
		case Rainbow:
			// (0, 0), (1/5, 1/6), (2/5, 2/6), (3/5, 3/6), (4/5, 4/6), (5/5, 5/6)
			for(int i=0; i<6; i++)
				{
				float index = i/5.0;
				addColor(index, QColor::fromHsvF(index*(5/6.0), 1.0, 1.0));
				}
			break;

		case OneValTest:
			addColor(0.25, QColor(Qt::red));
			break;

		case TwoValTest:
			addColor(0.25, QColor(Qt::red));
			addColor(0.75, QColor(Qt::cyan));
			break;
		}
	}


// Define an value in the color map.  index may be outside the normal range
// [0,1], but lookup indexes are clamped to [0,1]
void Colormap::addColor(float index, QColor color)
	{
	// insert the index directly into a sorted map
	m_colorMap[index] = color;
	m_hasAlpha = m_hasAlpha || (color.alphaF() < 1.0);
	}


QColor Colormap::lookup(float index)
	{
	// clamp index to the proper range [0,1]
	if(index < 0.0)
		{
		index = 0.0;
		}
	else if(index > 1.0)
		{
		index = 1.0;
		}

	// no map values defined?
	if(m_colorMap.empty())
		{
		return QColor(Qt::darkRed);
		}

	// The colormap values are not required to cover the entire range, so see
	// if the index is <= or >= the defined range:
	MapFloatToColorIter firstVal = m_colorMap.begin();
	if(index <= firstVal.key())
		return firstVal.value();

	MapFloatToColorIter lastVal = m_colorMap.end()-1;
	if(index >= lastVal.key())
		return lastVal.value();

	// Find "lower bound" iterator for the lookup index, so that
	// 		[lb-1] < index <= [lb] < [lb+1]
	MapFloatToColorIter lb = m_colorMap.lowerBound(index);

	// We know that begin() < index, so its safe to decrement the lower bound
	// ASSERT(lb != begin())
	MapFloatToColorIter lbPrev = lb-1;

	return interpColor(index, lbPrev.key(), lbPrev.value(), lb.key(), lb.value());
	}


// interpolate color values (in HSV)
QColor Colormap::interpColor(float v,
							 float val0, QColor col0,
							 float val1, QColor col1)
	{
	// extract values to interpolate
	qreal vals0[4] = { col0.hueF(), col0.saturationF(), col0.valueF(), col0.alphaF() };
	qreal vals1[4] = { col1.hueF(), col1.saturationF(), col1.valueF(), col1.alphaF() };

#if 0
	// XXX Should we adjust the Hue values to account for wrap around?
	// It seems fraught with danger, and it seems to reduce the user's
	// control.  The user will just have to understand what they are doing.
	qreal hueDelta = vals1[0] - vals0[0];
	if(fabs(hueDelta) > 0.5)
		{
		// XXX need to check out this logic
		vals0[0] = fmod(vals0[0], 1.0);
		vals1[0] = fmod(vals1[0], 1.0);
		if(vals1[0] - vals[0] > 0)
		}
#endif

	float t = (v - val0)/(val1 - val0);
	qreal newVals[4];
	for(int i=0; i<4; ++i)
		{
		newVals[i] = vals0[i] + t*(vals1[i] - vals0[i]);
		}

	return QColor::fromHsvF(newVals[0], newVals[1], newVals[2], newVals[3]);
	}


