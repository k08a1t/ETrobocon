//S)
#include "WhiteCondition.h"

#include "Condition/LineCondition.h"
#include "Measure/Brightness.h"
//E)

WhiteCondition::WhiteCondition(int BaseValue, Brightness* pBrightness)
//S)
:	m_BaseValue(BaseValue),
	m_pBrightness(pBrightness)
//E)
{
	//S)
	
	//E)
}

WhiteCondition::~WhiteCondition()
{
	//S)
	
	//E)
}

bool WhiteCondition::isSatisfy()
{
	//S)
	if(m_BaseValue <= m_pBrightness->getBrightness()){
		 return true;
	}
	else{
		return false;
	}
	//E)
}

//S)

//E)
