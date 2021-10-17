//S)
#include "DirectionCondition.h"
//E)

DirectionCondition::DirectionCondition(int t_adis, DistanceMeasure* pDistanceMeasure)
//S)
 : m_target_angle(t_adis),m_pDistanceMeasure(pDistanceMeasure)
//E)
{
	//S)
	
	//E)
}

DirectionCondition::~DirectionCondition()
{
	//S)
	
	//E)
}

bool DirectionCondition::isSatisfy()
{
	//S)
		int direction;
	direction = m_pDistanceMeasure->getBlockLeft() - m_pDistanceMeasure->getBlockRight();
	
	if(m_target_angle >=0){
		if(m_target_angle <= direction){
			return true;
		}
		else{
			return false;
		}
	}
	else{
		if(m_target_angle >= direction)
		
		{
			return true;
		}

		else
		{
			return false;
		}
	}	
	//E)
}

//S)

//E)
