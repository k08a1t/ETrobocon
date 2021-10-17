//S)

//E)

#ifndef RUNMETHOD_RATIOROTATIONMETHOD_H
#define RUNMETHOD_RATIOROTATIONMETHOD_H

//S)
#include "RunMethod/RunMethod.h"
#include "Motor.h"
#include "../Measure/DistanceMeasure.h"

using namespace ev3api;
//E)

class RatioRotationMethod : public RunMethod
{
	//S)
	
	//E)

private:

	double m_curve_coefficient;

	int m_curve_helper;

	int m_speed;

	int m_standard_B;

	int m_standard_C;

	int m_turn;

	DistanceMeasure* m_pDistanceMeasure;

public:

	void run();

	RatioRotationMethod(double c_coeff, int curve_h, int speed, Motor* pLeftMotor, Motor* pRightMotor, DistanceMeasure* pdistanceMeasure);

	~RatioRotationMethod();

	//S)
	
	//E)
};

//S)

//E)

#endif	// RUNMETHOD_RATIOROTATIONMETHOD_H

//S)

//E)
