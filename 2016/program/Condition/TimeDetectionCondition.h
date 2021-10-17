//S)

//E)

#ifndef CONDITION_TIMEDETECTIONCONDITION_H
#define CONDITION_TIMEDETECTIONCONDITION_H

//S)
#include "Condition/Condition.h"
#include "Clock.h"

using namespace ev3api;
//E)

class TimeDetectionCondition : public Condition
{
	//S)
	
	//E)

private:

	int m_target_time;

	int m_reset;

	int m_pre_time;

	Clock* m_pClock;

public:

	TimeDetectionCondition(int t_time, Clock* pClock);

	~TimeDetectionCondition();

	bool isSatisfy();

	//S)
	
	//E)
};

//S)

//E)

#endif	// CONDITION_TIMEDETECTIONCONDITION_H

//S)

//E)
