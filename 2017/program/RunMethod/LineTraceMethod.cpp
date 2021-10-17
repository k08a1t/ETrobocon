//S)
#include "LineTraceMethod.h"

#include "RunMethod/RunMethod.h"
#include "ColorSensor.h"
#include "Motor.h"
#include "RunMethod/PID.h"
#include "../Measure/Calibration.h"
using namespace ev3api;
//E)

LineTraceMethod::LineTraceMethod(int speed, int max, bool edge, int borderChange, Brightness* pBrightness, PID* pPID, Motor* pLeftMotor, Motor* pRightMotor)
//S)
:	m_speed(speed),
	m_turn_MAX(max),
	m_edge(edge),
	m_border_change(borderChange),
	m_pBrightness(pBrightness),
	m_pPID(pPID)
//E)
{
	//S)
	m_pLeftMotor=pLeftMotor;
	m_pRightMotor=pRightMotor;	
	//E)
}

void LineTraceMethod::run()
{
	//S)
	double pwm_L, pwm_R;// モータPWM出力 
	
	int steer;
	int light;

	light = m_pBrightness->getBrightness()+m_border_change;
	steer = m_pPID->calcControllValue(light);
	steer = (steer>m_turn_MAX)?m_turn_MAX:(steer<(m_turn_MAX*(-1)))?(m_turn_MAX*(-1)):steer;

	if(m_edge == 0){
		steer = steer*(-1);
	}

	pwm_L=m_speed+steer;
	pwm_R=m_speed-steer;


	m_pLeftMotor->setPWM(pwm_L); /* 左モータPWM出力セット(-100～100) */
	m_pRightMotor->setPWM(pwm_R); /* 右モータPWM出力セット(-100～100) */
	
	//E)
}

LineTraceMethod::~LineTraceMethod()
{
	//S)
	
	//E)
}

//S)

//E)
