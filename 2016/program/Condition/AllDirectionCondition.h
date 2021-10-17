//S)

//E)

#ifndef CONDITION_ALLDIRECTIONCONDITION_H
#define CONDITION_ALLDIRECTIONCONDITION_H

//S)
#include "Condition/Condition.h"
#include "Measure/DistanceMeasure.h"
//E)

class AllDirectionCondition : public Condition
{
	//S)
	
	//E)

private:

	int m_target_angle;

	bool m_LR;

	DistanceMeasure* m_pDistanceMeasure;

public:

	AllDirectionCondition(int t_adis, bool t_LR, DistanceMeasure* pDistanceMeasure);

	~AllDirectionCondition();

	bool isSatisfy();

	//S)
	
	//E)
};

//S)

//E)

#endif	// CONDITION_ALLDIRECTIONCONDITION_H

//S)

//E)
