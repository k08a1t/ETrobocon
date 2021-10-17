//S)

//E)

#ifndef ROUTEGUIDE_STARWATCHRUNBLOCK_H
#define ROUTEGUIDE_STARWATCHRUNBLOCK_H

//S)
#include "RouteGuide/RouteSearchRunblock.h"
#include "Measure/DistanceMeasure.h"
#include "Condition/Condition.h"
#include "RunMethod/RunMethod.h"
#include "Measure/StarReader.h"
#include "Mode/Mode.h"

using namespace ev3api;
//E)

class StarWatchRunBlock : public RouteSearchRunBlock
{
	//S)
	
	//E)

private:

	StarReader* m_pStarReader;

public:

	StarWatchRunBlock(int block_number, Condition* pCondition, RunMethod* pRunMethod, DistanceMeasure* pDistanceMeasure, Communication* pCommunication, Mode* pMode, DynamicRunArea* pDynamicRunArea, StarReader* pStarReader);

	bool start();

	void decideBranchNumber();

	~StarWatchRunBlock();

	//S)
	
	//E)
};

//S)

//E)

#endif	// ROUTEGUIDE_STARWATCHRUNBLOCK_H

//S)

//E)
