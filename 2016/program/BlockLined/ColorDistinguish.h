//S)

//E)

#ifndef BLOCKLINED_COLORDISTINGUISH_H
#define BLOCKLINED_COLORDISTINGUISH_H

//S)
#include "BlockLined/Color.h"
#include "ColorSensor.h"

using namespace ev3api;
//E)

class ColorDistinguish
{
	//S)
	
	//E)

private:

	rgb_raw_t m_RedReference;

	rgb_raw_t m_BlueReference;

	rgb_raw_t m_YellowReference;

	rgb_raw_t m_GreenReference;

	rgb_raw_t m_BlackReference;

	Color m_ColorDistinguish;

	int m_UnecidedDegree;

	int m_judge;

	ColorSensor* m_pColorSensor;

public:

	ColorDistinguish(ColorSensor* pColorSensor);

	Color BlockcolorDistinguish();

	~ColorDistinguish();

	//S)
	int m_log[3];
	void log(int &loga, int &logb, int &logc);
	//E)
};

//S)

//E)

#endif	// BLOCKLINED_COLORDISTINGUISH_H

//S)

//E)
