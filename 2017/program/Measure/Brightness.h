//S)

//E)

#ifndef MEASURE_BRIGHTNESS_H
#define MEASURE_BRIGHTNESS_H

//S)
#include "ColorSensor.h"

using namespace ev3api;
//E)

class Brightness
{
	//S)
	
	//E)

private:

	int m_border;

	int m_revision_brightness;

	ColorSensor* m_pColorSensor;

public:

	Brightness(ColorSensor* pColorSensor);

	int getBrightness();

	void setBorder(int border);

	~Brightness();

	//S)
	
	//E)
};

//S)

//E)

#endif	// MEASURE_BRIGHTNESS_H

//S)

//E)
