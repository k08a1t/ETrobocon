//S)
//Copyright (c) 2015 Kagaku No Yousei. All Rights Reserved.
//E)

#ifndef MEASURE_HSLMEASURE_H
#define MEASURE_HSLMEASURE_H

//S)
#include "Clock.h"
#include "ColorSensor.h"
#include "TouchSensor.h"

using namespace ev3api;
//E)

class HSLMeasure
{
	//S)
	
	//E)

private:

	ColorSensor* m_pColorSensor;

	int Result_HSL;

	int Sort[3];

    int Times;

public:

	HSLMeasure(ColorSensor* pColorSensor);

	int HSL_Decision(int times);

	~HSLMeasure();

	//S)
	
	//E)
};

//S)

//E)

#endif	// MEASURE_HSLMEASURE_H

//S)

//E)
