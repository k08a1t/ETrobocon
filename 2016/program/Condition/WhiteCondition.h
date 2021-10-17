//S)

//E)

#ifndef CONDITION_WHITECONDITION_H
#define CONDITION_WHITECONDITION_H

//S)
#include "Condition/Condition.h"
#include "Measure/Brightness.h"
//E)

class WhiteCondition : public Condition
{
	//S)
	
	//E)

private:

	int m_BaseValue;

	Brightness* m_pBrightness;

public:

	WhiteCondition(int BaseValue, Brightness* pBrightness);

	~WhiteCondition();

	bool isSatisfy();

	//S)
	
	//E)
};

//S)

//E)

#endif	// CONDITION_LINECONDITION_H

//S)

//E)
