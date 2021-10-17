//S)

//E)

#ifndef CONDITION_OBSTACLECONDITION_H
#define CONDITION_OBSTACLECONDITION_H

//S)
#include "Condition/Condition.h"
#include "Device/SonarMeter.h"
//E)

class ObstacleCondition : public Condition
{
	//S)
	
	//E)

private:

	int m_target_distance;

	int m_range;

	int m_reverse;

	SonarMeter* m_pSonarMeter;

public:

	ObstacleCondition(int Target, int range, int reverse, SonarMeter* pSonarMeter);

	bool isSatisfy();

	~ObstacleCondition();

	//S)
	
	//E)
};

//S)

//E)

#endif	// CONDITION_OBSTACLECONDITION_H

//S)

//E)
