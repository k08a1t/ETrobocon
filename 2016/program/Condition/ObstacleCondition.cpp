//S)
#include "ObstacleCondition.h"

#include "SonarMeter.h"
#include "kernel.h"

//E)

ObstacleCondition::ObstacleCondition(int Target, int range, int reverse, SonarMeter* pSonarMeter)
//S)
:	m_target_distance(Target), m_range(range), m_reverse(reverse), m_pSonarMeter(pSonarMeter)
//E)
{
	//S)
	
	//E)
}

bool ObstacleCondition::isSatisfy()
{
	//S)
	if (m_target_distance + m_range >= m_pSonarMeter->get() && m_target_distance - m_range <= m_pSonarMeter->get()){
		if (m_reverse == true){
			return false;
		}
		else{
			return true;
		}
	}
	else
	{
		if (m_reverse == true){
			return true;
		}
		else{
			return false;
		}
	}
	//E)
}

ObstacleCondition::~ObstacleCondition()
{
	//S)
	
	//E)
}

//S)

//E)
