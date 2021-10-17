//S)

//E)

#ifndef MEASURE_CALIBRATION_H
#define MEASURE_CALIBRATION_H

//S)
#include "Clock.h"
#include "GyroSensor.h"
#include "ColorSensor.h"
#include "TouchSensor.h"
#include "Measure/Brightness.h"

using namespace ev3api;
//E)

class Calibration
{
	//S)
	
	//E)

private:

	int m_black;

	int m_white;

	int m_gray;

	ColorSensor* m_pColorSensor;

	GyroSensor* m_pGyroSensor;

	Clock* m_pClock;

	TouchSensor* m_pTouchSensor;

	Brightness* m_pBrightness;

public:

	void calibrate();

	Calibration(TouchSensor* pTouchSensor, ColorSensor* pColorSensor, Clock* pClock, GyroSensor* pGyroSensor, Brightness* pBrightness);

	int getBlack();

	int getWhite();

	int getGray();

	int getBorder();

	int calBrightness();

	void rgbCalibration();

	~Calibration();

	//S)
	
	//E)
};

//S)

//E)

#endif	// MEASURE_CALIBRATION_H

//S)

//E)
