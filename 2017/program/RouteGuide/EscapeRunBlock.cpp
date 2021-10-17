//S)
#include "EscapeRunBlock.h"

#include "RouteGuide/Runblock.h"
#include "RouteGuide/RouteSearchRunBlock.h"
#include "Measure/DistanceMeasure.h"
#include "RunMethod/RunMethod.h"
#include "Condition/Condition.h"
#include "Communication/Communication.h"
#include "Mode/Mode.h"
#include "BlockLined/Solution.h"
#include "RouteGuide/DynamicRunArea.h"

using namespace ev3api;
//E)

EscapeRunBlock::EscapeRunBlock(int block_number, Condition* pCondition, RunMethod* pRunMethod, DistanceMeasure* pDistanceMeasure, Communication* pCommunication, Mode* pMode, DynamicRunArea* pDynamicRunArea, Solution* pEscapeSolution)
//S)
	:RouteSearchRunBlock(block_number,pCondition,pRunMethod,pDistanceMeasure,pCommunication,pMode,pDynamicRunArea),m_pEscapeSolution(pEscapeSolution)
//E)
{
	//S)
	
	//E)
}

bool EscapeRunBlock::start()
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

void EscapeRunBlock::decideBranchNumber()
{
	//S)
	int direction = m_pEscapeSolution->getEscapeDirecrion();
	m_pDynamicRunArea->setBranchNumber(direction);
	//E)
}

EscapeRunBlock::~EscapeRunBlock()
{
	//S)
	
	//E)
}

//S)

//E)
