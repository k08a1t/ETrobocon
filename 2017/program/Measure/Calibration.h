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
#include "Measure/HSLMeasure.h"

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

	unsigned int HSL_Red;

	unsigned int HSL_Yellow;

	unsigned int HSL_Blue;

	unsigned int HSL_Green;

	ColorSensor* m_pColorSensor;

	GyroSensor* m_pGyroSensor;

	Clock* m_pClock;

	TouchSensor* m_pTouchSensor;

	Brightness* m_pBrightness;

	HSLMeasure* m_pHSLMeasure;

public:

	void calibrate();

	Calibration(TouchSensor* pTouchSensor, ColorSensor* pColorSensor, Clock* pClock, GyroSensor* pGyroSensor, Brightness* pBrightnes, HSLMeasure* pHSLMeasure);

	int getBlack();

	int getWhite();

	int getGray();

	int getBorder();

	unsigned int getHSL_Red();

	unsigned int getHSL_Yellow();

	unsigned int getHSL_Blue();

	unsigned int getHSL_Green();

	int calBrightness();

	void rgbCalibration();

	void hslCalibration();

	void Display_Clean();

	void ResultHSL_Check();

	~Calibration();

	//S)
	
	//E)
};

//S)

//E)

#endif	// MEASURE_CALIBRATION_H

//S)

//E)
