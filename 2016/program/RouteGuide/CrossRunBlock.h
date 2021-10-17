//S)

//E)

#ifndef ROUTEGUIDE_CROSSRUNBLOCK_H
#define ROUTEGUIDE_CROSSRUNBLOCK_H

//S)
#include "Measure/DistanceMeasure.h"
#include "RunMethod/RunMethod.h"
#include "Condition/Condition.h"
#include "Communication/Communication.h"
#include "Mode/Mode.h"
#include "BlockLined/Solution.h"
#include "RouteGuide/DynamicRunArea.h"
#include "RouteGuide/RouteSearchRunBlock.h"
//E)

class CrossRunBlock : public RouteSearchRunBlock
{
	//S)
	
	//E)

private:

	Solution* m_pCourseSolution;

public:

	CrossRunBlock(int block_number, Condition* pCondition, RunMethod* pRunMethod, DistanceMeasure* pDistanceMeasure, Communication* pCommunication, Mode* pMode, DynamicRunArea* pDynamicRunArea, Solution* pCourseSolution);

	bool start();

	void decideBranchNumber();

	~CrossRunBlock();

	//S)
	
	//E)
};

//S)

//E)

#endif	// ROUTEGUIDE_CROSSRUNBLOCK_H

//S)

//E)
