//S)
#include "RatioRotationMethod.h"

#include "RunMethod/RunMethod.h"
#include "Motor.h"
#include "Measure/DistanceMeasure.h"

using namespace ev3api;
//E)

void RatioRotationMethod::run()
{
	//S)
	int result;
	static float m_curve_turn_pre;

	if(m_curve_coefficient >= 1){
		result =  (int)(m_pDistanceMeasure->getBlockLeft() *m_curve_coefficient);
		m_curve_turn_pre = ((m_pDistanceMeasure->getBlockRight()) - ( m_pDistanceMeasure->getBlockLeft())) - (result - (m_pDistanceMeasure->getBlockLeft()));
	}
	else{
		result =  (int)(m_pDistanceMeasure->getBlockRight() *1/m_curve_coefficient);
		m_curve_turn_pre = ((m_pDistanceMeasure->getBlockLeft()) - ( m_pDistanceMeasure->getBlockRight())) - (result - (m_pDistanceMeasure->getBlockRight()));
		m_curve_turn_pre = m_curve_turn_pre*-1;
	}

	m_turn = (int)m_curve_turn_pre + m_curve_helper;
		
	m_turn = (m_turn<-50)?-50:(m_turn>50)?50:m_turn;

	signed char pwm_L, pwm_R; /* 左右モータPWM出力 */
	pwm_L = m_speed;
	pwm_R = m_speed;
	
	if (m_turn >= 0){	/* 直進と右旋回命令のとき */
			 	
		pwm_R = m_speed - m_turn;
	}
	else{			/* 左旋回命令のとき */
		pwm_L = m_speed + m_turn;
	}
	
	pwm_L=(pwm_L>100)?100:(pwm_L<(-100))?(-100):pwm_L;
	pwm_R=(pwm_R>100)?100:(pwm_R<(-100))?(-100):pwm_R;

	m_pLeftMotor->setPWM(pwm_L); /* 左モータPWM出力セット(-100～100) */
	m_pRightMotor->setPWM(pwm_R); /* 右モータPWM出力セット(-100～100) */
	//E)
}

RatioRotationMethod::RatioRotationMethod(double c_coeff, int curve_h, int speed, Motor* pLeftMotor, Motor* pRightMotor, DistanceMeasure* pdistanceMeasure)
//S)
:	m_curve_coefficient(c_coeff),
	m_curve_helper(curve_h),
	m_speed(speed),
	m_standard_B(0),
	m_standard_C(0),
	m_turn(0),
	m_pDistanceMeasure(pdistanceMeasure)
//E)
{
	//S)
	m_pLeftMotor = pLeftMotor;
	m_pRightMotor = pRightMotor;	
	//E)
}

RatioRotationMethod::~RatioRotationMethod()
{
	//S)
	
	//E)
}

//S)

//E)
