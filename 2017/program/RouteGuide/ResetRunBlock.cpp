//S)
#include "ResetRunBlock.h"

#include "RouteGuide/Runblock.h"

using namespace ev3api;
//E)

bool ResetRunBlock::start()
{
	//S)
	bool buf = false;//�o�b�t�@�̏�����
	buf = m_pCondition -> isSatisfy();
	m_pRunMethod->run();
	m_pMode->decideMede();

	if (buf == true){
		m_pDistanceMeasure->resetAll();//�����v�����ׂĂO���Z�b�g����B�@�̂���~���Ă���Ƃ��Ɏg����
		m_pCommunication->setSound();
		return true;
	}
	else{
		return false;
	}	
	//E)
}

ResetRunBlock::ResetRunBlock(int block_number, Condition* pCondition, RunMethod* pRunMethod, DistanceMeasure* pDistanceMeasure, Communication* pCommunication, Mode* pMode)
//S)
: RunBlock(block_number,pCondition,pRunMethod,pDistanceMeasure,pCommunication,pMode)
//E)
{
	//S)
	
	//E)
}

ResetRunBlock::~ResetRunBlock()
{
	//S)
	
	//E)
}

//S)

//E)
