//S)

//E)

#ifndef MEASURE_STARREADER_H
#define MEASURE_STARREADER_H

//S)
#include "ColorSensor.h"

using namespace ev3api;
//E)

class StarReader
{
	//S)
	
	//E)

private:

	int m_star_color;

	int m_judge;

	ColorSensor* m_pColorSensor;

public:

	StarReader(ColorSensor* pColorSensor);

	void readStarSituation();

	int getStarSituation();

private:

	void checkStarColor();

public:

	~StarReader();

	//S)
	
	//E)
};

//S)

//E)

#endif	// MEASURE_STARREADER_H

//S)

//E)
