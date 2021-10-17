//S)

//E)

#ifndef ROUTEGUIDE_BLOCKWATCHRUNBLOCK_H
#define ROUTEGUIDE_BLOCKWATCHRUNBLOCK_H

//S)
#include "RouteSearchRunblock.h"
#include "../Measure/DistanceMeasure.h"
#include "../Condition/Condition.h"
#include "../RunMethod/RunMethod.h"
#include "../Measure/BlockReader.h"
#include "../Mode/Mode.h"
#include "RouteGuide/DynamicRunArea.h"
#include "../Communication/Communication.h"

using namespace ev3api;
//E)

class BlockWatchRunBlock : public RouteSearchRunBlock
{
	//S)
	
	//E)

private:

	BlockReader* m_pBlockReader;

public:

	BlockWatchRunBlock(int block_number, Condition* pCondition, RunMethod* pRunMethod, DistanceMeasure* pDistanceMeasure, Communication* pCommunication, Mode* pMode, DynamicRunArea* pDynamicRunArea, BlockReader* pBlockReader);

	bool start();

	void decideBranchNumber();

	~BlockWatchRunBlock();

	//S)
	
	//E)
};

//S)

//E)

#endif	// ROUTEGUIDE_BLOCKWATCHRUNBLOCK_H

//S)

//E)
