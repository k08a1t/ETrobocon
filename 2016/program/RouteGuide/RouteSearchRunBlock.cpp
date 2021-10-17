//S)
#include "RouteSearchRunBlock.h"

#include "RouteGuide/Runblock.h"
#include "RouteGuide/DynamicRunArea.h"

using namespace ev3api;
//E)

RouteSearchRunBlock::RouteSearchRunBlock(int block_number, Condition* pCondition, RunMethod* pRunMethod, DistanceMeasure* pDistanceMeasure, Communication* pCommunication, Mode* pMode, DynamicRunArea* pDynamicRunArea)
//S)
: RunBlock(block_number,pCondition,pRunMethod,pDistanceMeasure,pCommunication,pMode),m_pDynamicRunArea(pDynamicRunArea)
//E)
{
	//S)
	
	//E)
}

RouteSearchRunBlock::~RouteSearchRunBlock()
{
	//S)
	
	//E)
}

//S)

//E)
