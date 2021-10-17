//S)
//Copyright (c) 2016 Kagaku No Yousei. All Rights Reserved.
#include "DistanceCondition.h"

//E)

DistanceCondition::DistanceCondition(int t_adis, DistanceMeasure* pDistanceMeasure)
//S)
  : m_target_block_distance(t_adis),m_pDistanceMeasure(pDistanceMeasure)
//E)
{
	//S)
	
	//E)
}

DistanceCondition::~DistanceCondition()
{
	//S)
	
	//E)
}

bool DistanceCondition::isSatisfy()
{
	//S)
	int distance;
	distance = m_pDistanceMeasure->getBlock();

	if(m_target_block_distance >= 0){
		if(m_target_block_distance <= distance)
		{
			return true;
		}

		else
		{
			return false;
		}
	}
	else{
		if(m_target_block_distance >= distance)
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
