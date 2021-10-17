//S)

//E)

#ifndef CONDITION_MULTICONDITION_H
#define CONDITION_MULTICONDITION_H

//S)
#include "Condition/Condition.h"
//E)

class MultiCondition : public Condition
{
	//S)
	
	//E)

private:

	bool m_logic;

	Condition* m_pFirstCondition;

	Condition* m_pSecondCondition;

public:

	MultiCondition(bool logic, Condition* pConditionA, Condition* pConditionB);

	~MultiCondition();

	bool isSatisfy();

	//S)
	
	//E)
};

//S)

//E)

#endif	// CONDITION_MULTICONDITION_H

//S)

//E)
