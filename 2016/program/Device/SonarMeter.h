//S)

//E)

#ifndef DEVICE_SONARMETER_H
#define DEVICE_SONARMETER_H

//S)
#include "SonarSensor.h"

using namespace ev3api;
//E)

class SonarMeter
{
	//S)
	
	//E)

private:

	int m_distance;

	int m_count;

	SonarSensor* m_pSonarSensor;

public:

	SonarMeter(SonarSensor* pSonarSensor);

	void ReadDistance();

	int get();

	~SonarMeter();

	//S)
	
	//E)
};

//S)

//E)

#endif	// DEVICE_SONARMETER_H

//S)

//E)
