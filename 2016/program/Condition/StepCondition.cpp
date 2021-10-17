//S)
#include "StepCondition.h"

//E)


StepCondition::StepCondition(int t_gyro, int t_speed, GyroSensor* pGyroSensor, SpeedoMeter* pSpeedoMeter)
//S)
  : m_target_gyro(t_gyro),m_target_speed(t_speed),m_pSpeedoMeter(pSpeedoMeter)
//E)
{
	//S)
	m_pGyroSensor=pGyroSensor;
	//E)
}

bool StepCondition::isSatisfy()
{
	//S)
	m_log[1] = m_pGyroSensor->getAnglerVelocity();

	if( m_target_gyro <= m_pGyroSensor->getAnglerVelocity()|| m_target_gyro * -1 > m_pGyroSensor->getAnglerVelocity()||m_target_speed > m_pSpeedoMeter->get()){
		
		return true;
	}
	
	else
	{
		return false;
	}
	//E)
}

StepCondition::~StepCondition()
{
	//S)
	
	//E)
}

//S)
void StepCondition::log(int &loga, int &logb, int &logc)
{
	loga = m_log[0];
	logb = m_log[1];
	logc = m_log[2];
}
//E)
