// ˅
#include "Condition.h"
#include "DistanceMeter.h"
#include "Form.h"
#include "RunMethod.h"
#include "RunSection.h"


// ˄

RunSection::RunSection(int section_number, Condition* pCondition, RunMethod* pRunMethod, DistanceMeter pDistanceMeter, Form* pForm)
	// ˅
	:m_section_number(0),m_pCondition(pCondition),m_pRunMethod(pRunMethod),m_pDistanceMeter(pDistanceMeter),m_pForm(pForm)
	// ˄
{
	// ˅
	
	// ˄
}

bool RunSection::start()
{
	// ˅
	bool buf = false;//バッファの初期化
	buf = m_pCondition->satisfy();
	m_pRunMethod->run();
	m_pForm->changeForm();

	if (buf == true) {
		m_pDistanceMeter->resetMeasure();
		return true;
	}
	else {
		return false;
	}
	// ˄
}

RunSection::~RunSection()
{
	// ˅
	
	// ˄
}

// ˅

// ˄
