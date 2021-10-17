//S)
#include "InstructionMethod.h"

#include "RunMethod/RunMethod.h"
#include "Motor.h"
using namespace ev3api;
//E)

InstructionMethod::InstructionMethod(int speedl, int speedr, Motor* pLeftMotor, Motor* pRightMotor)
//S)
:	m_speed_L(speedl),
	m_speed_R(speedr)
//E)
{
	//S)
	m_pLeftMotor = pLeftMotor;
	m_pRightMotor = pRightMotor;	
	//E)
}

void InstructionMethod::run()
{
	//S)
	signed char pwm_L, pwm_R;
	pwm_L = (int)m_speed_L;
	pwm_R = (int)m_speed_R;


		
	m_pLeftMotor->setPWM(pwm_L); /* 左モータPWM出力セット(-100～100) */
	m_pRightMotor->setPWM(pwm_R); /* 右モータPWM出力セット(-100～100) */
	//E)
}

InstructionMethod::~InstructionMethod()
{
	//S)
	
	//E)
}

//S)

//E)
