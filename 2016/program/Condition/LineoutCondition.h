//S)

//E)

#ifndef CONDITION_LINEOUTCONDITION_H
#define CONDITION_LINEOUTCONDITION_H

//S)
#include "Condition/Condition.h"
#include "Measure/Brightness.h"
//E)

class LineoutCondition : public Condition
{
	//S)
	
	//E)

private:

	//int m_BaseCount;
	int m_TargetCount;
	int m_BaseValue;
	int m_Count;

	//m_Count* Count;
	Brightness* m_pBrightness;
	//Count* m_Count;
	//TargetCount* m_TargetCount;

public:

	LineoutCondition(int TargetCount,int BaseValue,Brightness* pBrightness);

	~LineoutCondition();

	bool isSatisfy();

	//S)
	
	//E)
};

//S)

//E)

#endif	// CONDITION_LINECONDITION_H

//S)

//E)
