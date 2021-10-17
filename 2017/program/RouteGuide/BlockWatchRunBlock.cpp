//S)
#include "BlockWatchRunBlock.h"

#include "RouteSearchRunBlock.h"
#include "../RouteGuide/DistanceMeasure.h"
#include "../Condition/Condition.h"
#include "../RunMethod/RunMethod.h"
#include "../Measure/BlockReader.h"
#include "../Mode/Mode.h"
#include "RouteGuide/DynamicRunArea.h"
#include "../Communication/Communication.h"

using namespace ev3api;
//E)

BlockWatchRunBlock::BlockWatchRunBlock(int block_number, Condition* pCondition, RunMethod* pRunMethod, DistanceMeasure* pDistanceMeasure, Communication* pCommunication, Mode* pMode, DynamicRunArea* pDynamicRunArea, BlockReader* pBlockReader)
//S)
:RouteSearchRunBlock(block_number,pCondition,pRunMethod,pDistanceMeasure,pCommunication,pMode,pDynamicRunArea),m_pBlockReader(pBlockReader)
//E)
{
	//S)
	
	//E)
}

bool BlockWatchRunBlock::start()
{
	//S)
	bool buf = false;//バッファの初期化
	buf = m_pCondition -> isSatisfy();
	m_pRunMethod->run();
	m_pMode->decideMede();
	m_pBlockReader->readBlockSituation();
	
	if (buf == true){
		m_pDistanceMeasure->resetBlock();
		decideBranchNumber();
		m_pCommunication->setSound();
		
		return true;
	}
	else{
		return false;
	}
	//E)
}

void BlockWatchRunBlock::decideBranchNumber()
{
	//S)
	int color = m_pBlockReader->getBlockSituation();
	
	m_pDynamicRunArea->setBranchNumber(color);
	//E)
}

BlockWatchRunBlock::~BlockWatchRunBlock()
{
	//S)
	
	//E)
}

//S)

//E)
