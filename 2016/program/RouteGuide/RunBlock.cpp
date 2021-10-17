//S)
#include "RunBlock.h"

#include "Measure/DistanceMeasure.h"
#include "RunMethod/RunMethod.h"
#include "Condition/Condition.h"
#include "Communication/Communication.h"
#include "Mode/Mode.h"

using namespace ev3api;
//E)

bool RunBlock::start()
{
	//S)
	bool buf = false;//バッファの初期化
	buf = m_pCondition -> isSatisfy();
	m_pRunMethod->run();
	m_pMode->decideMede();

	if (buf == true){
		m_pDistanceMeasure->resetBlock();
		m_pCommunication->setSound();
		return true;
	}
	else{
		return false;
	}
	//E)
}

RunBlock::RunBlock(int block_number, Condition* pCondition, RunMethod* pRunMethod, DistanceMeasure* pDistanceMeasure, Communication* pCommunication, Mode* pMode)
//S)
 :m_block_number(block_number),m_pCondition(pCondition),m_pDistanceMeasure(pDistanceMeasure),m_pRunMethod(pRunMethod),m_pCommunication(pCommunication),m_pMode(pMode)
//E)
{
	//S)
	
	//E)
}

int RunBlock::getBlockNumber()
{
	//S)
	return m_block_number;
	//E)
}

RunBlock::~RunBlock()
{
	//S)
	
	//E)
}

//S)

//E)
