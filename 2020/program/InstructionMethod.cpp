// ˅
#include "InstructionMethod.h"
#include "Motor.h"


// ˄

InstructionMethod::InstructionMethod(int speed_L, int speed_R, Motor* pLeftMotor, Motor* pRightMotor)
	// ˅
	:m_left_speed(speed_L),m_right_speed(speed_R),m_pLeftMotor(pLeftMotor),m_pRightMotor(pRightMotor)
	// ˄
{
	// ˅
	
	// ˄
}

void InstructionMethod::run()
{
	// ˅
	char pwm_L;
	char pwm_R;
	pwm_L = (int)m_left_speed;
	pwm_R = (int)m_right_speed;

	m_pLeftMotor->setPWM(pwm_L);
	m_pRightMotor->setPWM(pwm_R);

	// ˄
}

InstructionMethod::~InstructionMethod()
{
	// ˅
	
	// ˄
}

// ˅

// ˄
