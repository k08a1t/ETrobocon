//S)
#include "DirectionMethod.h"

#include "RunMethod/RunMethod.h"
#include "Motor.h"
#include "Measure/DistanceMeasure.h"
using namespace ev3api;
//E)

void DirectionMethod::run()
{
	//S)
	
	//E)
}

DirectionMethod::DirectionMethod(int speed, int direction, Motor* pLeftMotor, Motor* pRightMotor, DistanceMeasure* pdistanceMeasure)
//S)
:	m_speed(speed), 
	m_pDistanceMeasure(pdistanceMeasure)
//E)
{
	//S)
	m_pLeftMotor = pLeftMotor;
	m_pRightMotor = pRightMotor;
	//E)
}

DirectionMethod::~DirectionMethod()
{
	//S)
	int result;

	if(m_pDistanceMeasure->getgetDirection() < )

	signed char pwm_L, pwm_R;
	pwm_L = (int)m_speed_L;
	pwm_R = (int)m_speed_R;

	m_pLeftMotor->setPWM(pwm_L); /* 左モータPWM出力セット(-100～100) */
	m_pRightMotor->setPWM(pwm_R); /* 右モータPWM出力セット(-100～100) */

	//E)
}

//S)

//E)
