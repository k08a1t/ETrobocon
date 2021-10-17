//S)
#include "SonarMeter.h"

//E)

SonarMeter::SonarMeter(SonarSensor* pSonarSensor)
//S)
: m_pSonarSensor(pSonarSensor)
//E)
{
	//S)
	m_count = 0;
	//E)
}

void SonarMeter::ReadDistance()
{
	//S)
	m_count++;
	if(m_count >= 3){
		m_distance=m_pSonarSensor->getDistance();
		m_count = 0;
	}
	//E)
}

int SonarMeter::get()
{
	//S)
	return m_distance;
	//E)
}

SonarMeter::~SonarMeter()
{
	//S)
	
	//E)
}

//S)

//E)
