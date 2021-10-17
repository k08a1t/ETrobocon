//S)
#include "LookblockRunBlock.h"

#include "RouteGuide/Runblock.h"
#include "BlockLined/Solution.h"

using namespace ev3api;
//E)

bool LookblockRunBlock::start()
{
	//S)
	bool buf = false;//�o�b�t�@�̏�����
	buf = m_pCondition -> isSatisfy();
	m_pRunMethod->run();
	m_pMode->decideMede();
	m_pLookSolution->searchBlockcolor();//�u���b�N�̐F�𒲂ׂ�

	if (buf == true){
		m_pLookSolution->LCDout();//��ʕ\��
		m_pDistanceMeasure->resetBlock();
		m_pCommunication->setSound();
		return true;
	}
	else{
		return false;
	}	
	//E)
}

LookblockRunBlock::LookblockRunBlock(int block_number, Condition* pCondition, RunMethod* pRunMethod, DistanceMeasure* pDistanceMeasure, Communication* pCommunication, Mode* pMode, Solution* pSolution)
//S)
: RunBlock(block_number,pCondition,pRunMethod,pDistanceMeasure,pCommunication,pMode),m_pLookSolution(pSolution)
//E)
{
	//S)
	
	//E)
}

LookblockRunBlock::~LookblockRunBlock()
{
	//S)
	
	//E)
}

//S)

//E)
