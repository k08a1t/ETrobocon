//S)

//E)

#ifndef ROUTEGUIDE_TRAINWATCHRUNBLOCK_H
#define ROUTEGUIDE_TRAINWATCHRUNBLOCK_H

//S)
#include "RouteGuide/RouteSearchRunblock.h"
#include "Measure/TrainReader.h"
#include "Measure/DistanceMeasure.h"
#include "Condition/Condition.h"
#include "RunMethod/RunMethod.h"

using namespace ev3api;
//E)

class TrainWatchRunBlock : public RouteSearchRunBlock
{
	//S)
	
	//E)

private:

	TrainReader* m_pTrainReader;

public:

	bool start();

	void branchNumber();

	TrainWatchRunBlock(int block_number, Condition* pCondition, RunMethod* pRunMethod, DistanceMeasure* pDistanceMeasure, Communication* pCommunication, DynamicRunArea* pDynamicRunArea, Mode* pMode, TrainReader* pTrainReader);

	~TrainWatchRunBlock();

	//S)
	
	//E)
};

//S)

//E)

#endif	// ROUTEGUIDE_TRAINWATCHRUNBLOCK_H

//S)

//E)
