//S)

//E)

#ifndef CONDITION_STEPCONDITION_H
#define CONDITION_STEPCONDITION_H

//S)
#include "../Measure/SpeedoMeter.h"
#include "Condition/Condition.h"
#include "GyroSensor.h"

using namespace ev3api;
//E)


class StepCondition : public Condition
{
	//S)
	
	//E)

private:

	int m_target_gyro;

	int m_target_speed;

	SpeedoMeter* m_pSpeedoMeter;

	GyroSensor* m_pGyroSensor;

public:

	StepCondition(int t_gyro, int t_speed, GyroSensor* pGyroSensor, SpeedoMeter* pSpeedoMeter);

	bool isSatisfy();

	~StepCondition();

	//S)
	int m_log[3] = { 0 };
	void log(int &loga, int &logb, int &logc);
	//E)
};

//S)

//E)

#endif	// CONDITION_STEPCONDITION_H

//S)

//E)
