//S)
#include "StarWatchRunBlock.h"

#include "RouteGuide/RouteSearchRunBlock.h"
#include "Measure/DistanceMeasure.h"
#include "Condition/Condition.h"
#include "RunMethod/RunMethod.h"
#include "Measure/StarReader.h"
#include "Mode/Mode.h"

using namespace ev3api;
//E)

StarWatchRunBlock::StarWatchRunBlock(int block_number, Condition* pCondition, RunMethod* pRunMethod, DistanceMeasure* pDistanceMeasure, Communication* pCommunication, Mode* pMode, DynamicRunArea* pDynamicRunArea, StarReader* pStarReader)
//S)
:RouteSearchRunBlock(block_number,pCondition,pRunMethod,pDistanceMeasure,pCommunication,pMode,pDynamicRunArea),m_pStarReader(pStarReader)
//E)
{
	//S)
	
	//E)
}

bool StarWatchRunBlock::start()
{
	//S)
	bool buf = false;//バッファの初期化
	buf = m_pCondition -> isSatisfy();
	m_pRunMethod->run();
	m_pMode->decideMede();
	m_pStarReader->readStarSituation();
	
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

void StarWatchRunBlock::decideBranchNumber()
{
	//S)
	int color = m_pStarReader->getStarSituation();
	int bnum;
    if(color == 1){
    	bnum = 10304;
     }
    else if(color ==2 ){
    	bnum = 10203;
     }
    else if(color == 3){
    	bnum = 20304;
     }
    else{
    	bnum = 10204;
     }
	m_pDynamicRunArea->setBranchNumber(bnum);
	//E)
}

StarWatchRunBlock::~StarWatchRunBlock()
{
	//S)
	
	//E)
}

//S)

//E)
