//S)

//E)

#ifndef CONDITION_LINECONDITION_H
#define CONDITION_LINECONDITION_H

//S)
#include "Condition/Condition.h"
#include "Measure/Brightness.h"
//E)

class LineCondition : public Condition
{
	//S)
	
	//E)

private:

	int m_BaseValue;

	Brightness* m_pBrightness;

public:

	LineCondition(int BaseValue, Brightness* pBrightness);

	~LineCondition();

	bool isSatisfy();

	//S)
	
	//E)
};

//S)

//E)

#endif	// CONDITION_LINECONDITION_H

//S)

//E)
