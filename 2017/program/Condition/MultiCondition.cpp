//S)
#include "MultiCondition.h"

#include "kernel.h"

//E)

MultiCondition::MultiCondition(bool logic, Condition* pConditionA, Condition* pConditionB)
//S)
:	m_logic(logic),
	m_pFirstCondition(pConditionA),
	m_pSecondCondition(pConditionB)
//E)
{
	//S)
	
	//E)
}

MultiCondition::~MultiCondition()
{
	//S)
	
	//E)
}

bool MultiCondition::isSatisfy()
{
	//S)
	if(m_logic==true)
	{
		if(true == m_pFirstCondition->isSatisfy() || m_pSecondCondition->isSatisfy())
		{
			return true;
		}else{
			return false;
		}
	}	else{
		if(true == m_pFirstCondition->isSatisfy() && m_pSecondCondition->isSatisfy())
		{
			return true;
		}else{
			return false;
		}
	}
	//E)
}

//S)

//E)
