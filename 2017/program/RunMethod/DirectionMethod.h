//S)

//E)

#ifndef RUNMETHOD_DIRECTIONMETHOD_H
#define RUNMETHOD_DIRECTIONMETHOD_H

//S)
#include "DirectionMethod.h"
#include "Motor.h"
using namespace ev3api;
//E)

class DirectionMethod : public RunMethod
{
	//S)
	
	//E)

private:

	int m_speed;

	int m_tDirection;

	int m_standard_B;

	int m_standard_C;

	DistanceMeasure* m_pDistanceMeasure;

public:

	void run();

	DirectionMethod(int speed, int direction, Motor* pLeftMotor, Motor* pRightMotor, DistanceMeasure* pdistanceMeasure);

	~DirectionMethod();

	//S)
	
	//E)
};

//S)

//E)

#endif	// RUNMETHOD_DIRECTIONMETHOD_H

//S)

//E)
