//S)

//E)

#ifndef CONDITION_DISTANCECONDITION_H
#define CONDITION_DISTANCECONDITION_H

//S)
#include "Condition/Condition.h"
#include "Measure/DistanceMeasure.h"

using namespace ev3api;
//E)

class DistanceCondition : public Condition
{
	//S)
	
	//E)

private:

	int m_target_block_distance;

	DistanceMeasure* m_pDistanceMeasure;

public:

	DistanceCondition(int t_adis, DistanceMeasure* pDistanceMeasure);

	~DistanceCondition();

	bool isSatisfy();

	//S)
	
	//E)
};

//S)

//E)

#endif	// CONDITION_DISTANCECONDITION_H

//S)

//E)
