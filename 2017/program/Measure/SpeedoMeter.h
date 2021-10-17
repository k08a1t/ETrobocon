//S)

//E)

#ifndef MEASURE_SPEEDOMETER_H
#define MEASURE_SPEEDOMETER_H

//S)
#include "DistanceMeasure.h"

using namespace ev3api;
//E)

class SpeedoMeter
{
	//S)
	
	//E)

private:

	int m_now_speed;

	int m_num;

	int m_count[11];

	DistanceMeasure* m_pDistanceMeasure;

public:

	SpeedoMeter(DistanceMeasure* pDistanceMeasure);

	void update();

	int get();

	~SpeedoMeter();

	//S)
	
	//E)
};

//S)

//E)

#endif	// MEASURE_SPEEDOMETER_H

//S)

//E)
