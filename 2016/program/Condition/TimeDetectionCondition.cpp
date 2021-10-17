//S)
//Copyright (c) 2016 Kagaku No Yousei. All Rights Reserved.

#include "TimeDetectionCondition.h"

//E)

TimeDetectionCondition::TimeDetectionCondition(int t_time, Clock* pClock)
//S)
: m_target_time(t_time),m_reset(true),m_pre_time(0),m_pClock(pClock)
//E)
{
	//S)
	
	//E)
}

TimeDetectionCondition::~TimeDetectionCondition()
{
	//S)
	
	//E)
}

bool TimeDetectionCondition::isSatisfy()
{
	//S)
	if (m_reset == true){
		
		m_pre_time = m_pClock -> now();
		m_reset = false;
	}


	if(m_target_time < static_cast<int>(m_pClock -> now() - m_pre_time)){

		m_reset = true;

		return true;
	}
	
	else
	{
		return false;
	}
	//E)
}

//S)

//E)
