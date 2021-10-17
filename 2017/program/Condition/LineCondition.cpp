//S)
#include "LineCondition.h"

#include "Condition/LineCondition.h"
#include "../Measure/Brightness.h"
//E)

LineCondition::LineCondition(int BaseValue, Brightness* pBrightness)
//S)
:	m_BaseValue(BaseValue),
	m_pBrightness(pBrightness)
//E)
{
	//S)
	
	//E)
}

LineCondition::~LineCondition()
{
	//S)
	
	//E)
}

bool LineCondition::isSatisfy()
{
	//S)
	if(m_BaseValue >= m_pBrightness->getBrightness()){
		 return true;
	}
	else{
		return false;
	}
	//E)
}

//S)

//E)
