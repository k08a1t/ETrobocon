// ˅
#include "Clock.h"
#include "Form.h"
#include "Motor.h"

using namespace ev3api;
// ˄

Form::Form(int arm_position, Motor* pArmMotor, Clock* pClock)
	// ˅
	:m_arm_position(arm_position),m_pArmMotor(pArmMotor),m_pClock(pClock)
	// ˄
{
	// ˅
	
	// ˄
}

void Form::changeForm()
{
	// ˅
	double pwm_Arm = 30;
	double i_con = 0.01;
	int i_value;

	int arm = m_pArmMotor->getCount();
	i_value = (arm > m_arm_position + 3) ? 0 : (arm < m_arm_position - 3) ? 0 : m_i_valu + (m_arm_position - arm) * i_con;

	if (arm == m_arm_position || arm == m_arm_position + 1) {
		pwm_Arm = 0 + m_i_value;
	}
	else if (arm < m_arm_position) {
		pwm_Arm = 30 + m_i_value;
	}
	else {
		pwm_Arm = -5 + m_i_value;
	}
	m_pArmMotor->setPWM(pwm_Arm);

	// ˄
}

Form::~Form()
{
	// ˅
	
	// ˄
}

// ˅

// ˄
