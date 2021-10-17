//S)

//E)

#ifndef CONDITION_DIRECTIONCONDITION_H
#define CONDITION_DIRECTIONCONDITION_H

//S)
#include "Condition/Condition.h"
#include "../Measure/DistanceMeasure.h"
//E)

class DirectionCondition : public Condition
{
	//S)
	
	//E)

private:

	int m_target_angle;

	DistanceMeasure* m_pDistanceMeasure;

public:

	DirectionCondition(int t_adis, DistanceMeasure* pDistanceMeasure);

	~DirectionCondition();

	bool isSatisfy();

	//S)
	
	//E)
};

//S)

//E)

#endif	// CONDITION_DIRECTIONCONDITION_H

//S)

//E)
