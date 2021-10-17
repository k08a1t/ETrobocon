//S)
#include "CrossRunBlock.h"

#include "../RouteGuide/Runblock.h"
#include "../Measure/DistanceMeasure.h"
#include "../RunMethod/RunMethod.h"
#include "../Condition/Condition.h"
#include "../Communication/Communication.h"
#include "../Mode/Mode.h"
#include "../BlockLay/BlockLayScenario.h"
#include "../RouteGuide/DynamicRunArea.h"
using namespace ev3api;
//E)

CrossRunBlock::CrossRunBlock(int block_number, Condition* pCondition, RunMethod* pRunMethod, DistanceMeasure* pDistanceMeasure, Communication* pCommunication, Mode* pMode, DynamicRunArea* pDynamicRunArea, BlockLayScenario* pCourseScenario)
//S)
	:RouteSearchRunBlock(block_number, pCondition, pRunMethod, pDistanceMeasure, pCommunication, pMode, pDynamicRunArea),m_pCourseScenario(pCourseScenario)
//E)
{
	//S)
	
	//E)
}

bool CrossRunBlock::start()
{
	//S)
	bool buf = false;//バッファの初期化
	buf = m_pCondition->isSatisfy();
	m_pRunMethod->run();
	m_pMode->decideMede();

	if (buf == true) {
		m_pDistanceMeasure->resetBlock();
		m_pCommunication->setSound();
		decideBranchNumber();
		return true;
	}
	else {
		return false;
	}
	//E)
}

void CrossRunBlock::decideBranchNumber()
{
	//S)
	int direction = m_pCourseScenario->getCouse();
	m_pDynamicRunArea->setBranchNumber(direction);
	//E)
}

CrossRunBlock::~CrossRunBlock()
{
	//S)
	
	//E)
}

//S)

//E)
