//S)
#include "AllDirectionCondition.h"	
//E)

AllDirectionCondition::AllDirectionCondition(int t_adis, bool t_LR, DistanceMeasure* pDistanceMeasure)
//S)
	: m_target_angle(t_adis), m_LR(t_LR),m_pDistanceMeasure(pDistanceMeasure)
//E)
{
	//S)
	
	//E)
}

AllDirectionCondition::~AllDirectionCondition()
{
	//S)
 	
	//E)
}

bool AllDirectionCondition::isSatisfy()
{
	//S)
	int direction = m_pDistanceMeasure->getDirection();
	
	if(m_LR == true){
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
