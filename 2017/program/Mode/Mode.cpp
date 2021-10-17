//S)
#include "Mode.h"

#include "Motor.h"
#include "Clock.h"

using namespace ev3api;
//E)

Mode::Mode(int arm_pos, Motor* pArmMotor, Clock* pClock)
//S)
:	m_arm_pos(arm_pos),m_pClock(pClock)
//E)
{
	//S)
	m_pArmMotor = pArmMotor;
	//E)
}

void Mode::decideMede()
{
	//S)
	double pwm_S = 30;
	double i_con = 0.01;

	int arm = m_pArmMotor->getCount();

	m_i_valu=(arm > m_arm_pos + 10)?0:(arm < m_arm_pos - 10)?0:m_i_valu + (m_arm_pos - arm) * i_con;

	if (arm > m_arm_pos - 5 && arm < m_arm_pos + 5){
		pwm_S = 0 + m_i_valu;
	}
	else if (arm < m_arm_pos) {
		pwm_S = 20 + m_i_valu;//Rcourse‚Å‚Í20
	}
	else {
		pwm_S = -5 + m_i_valu;
	}
	m_pArmMotor->setPWM(pwm_S);
	//E)
}

void Mode::preMode()
{
	//S)
	m_pArmMotor->setPWM(-5);
	m_pClock->wait(1000);
	m_pArmMotor->reset();
	double pwm_S = 30;
	int arm;

	for(int a = 0; a<=250; a++){
		arm = m_pArmMotor->getCount();
		if (arm >= 30 && arm <= 32) {
			pwm_S = 0;
		}
		else if (arm < 30) {
			pwm_S = 3;
		}
		else {
			pwm_S = -3;
		}
		m_pArmMotor->setPWM(pwm_S);
		m_pClock->wait(4);
	}
	m_pArmMotor->setPWM(0);
	//E)
}

Mode::~Mode()
{
	//S)
	
	//E)
}

//S)

//E)
