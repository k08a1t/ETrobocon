//S)
#include "TrainWatchRunBlock.h"

#include "RouteGuide/RouteSearchRunblock.h"
#include "Measure/TrainReader.h"
#include "Measure/DistanceMeasure.h"
#include "Condition/Condition.h"
#include "RunMethod/RunMethod.h"

using namespace ev3api;
//E)

bool TrainWatchRunBlock::start()
{
	//S)
	bool buf = false;//�o�b�t�@�̏�����
	buf = m_pCondition->isSatisfy();
	m_pRunMethod->run();
	m_pTrainReader->readTrainSituation();
	if (buf == true){
		m_pDistanceMeasure->resetBlock();
		int buf2;
		char BUF2[32];
		buf2 = m_pTrainReader->getTrainSituation();
		sprintf(BUF2,"bu2=%d",buf2);
		ev3_lcd_draw_string(BUF2,0,0);
		m_pDynamicRunArea->setBranchNumber(buf2);
		//�K�v�Ȃ炱����ev3_speaker_play_tone(NOTE_C4, 100);�����
		return true;
	}
	else{
		return false;
	}
	//E)
}

void TrainWatchRunBlock::branchNumber()
{
	//S)
	
	//E)
}

TrainWatchRunBlock::TrainWatchRunBlock(int block_number, Condition* pCondition, RunMethod* pRunMethod, DistanceMeasure* pDistanceMeasure, Communication* pCommunication, DynamicRunArea* pDynamicRunArea, Mode* pMode, TrainReader* pTrainReader)
//S)
:RouteSearchRunBlock(block_number,pCondition,pRunMethod,pDistanceMeasure,pCommunication,pMode,pDynamicRunArea),m_pTrainReader(pTrainReader)

//E)
{
	//S)
	
	//E)
}

TrainWatchRunBlock::~TrainWatchRunBlock()
{
	//S)
	
	//E)
}

//S)

//E)
