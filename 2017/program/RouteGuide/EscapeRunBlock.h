//S)

//E)

#ifndef ROUTEGUIDE_ESCAPERUNBLOCK_H
#define ROUTEGUIDE_ESCAPERUNBLOCK_H

//S)
#include "RouteGuide/Runblock.h"
#include "RouteGuide/RouteSearchRunBlock.h"
#include "Measure/DistanceMeasure.h"
#include "RunMethod/RunMethod.h"
#include "Condition/Condition.h"
#include "Communication/Communication.h"
#include "Mode/Mode.h"
#include "BlockLined/Solution.h"
#include "RouteGuide/DynamicRunArea.h"

using namespace ev3api;
//E)

class EscapeRunBlock : public RouteSearchRunBlock
{
	//S)
	
	//E)

private:

	Solution* m_pEscapeSolution;

public:

	EscapeRunBlock(int block_number, Condition* pCondition, RunMethod* pRunMethod, DistanceMeasure* pDistanceMeasure, Communication* pCommunication, Mode* pMode, DynamicRunArea* pDynamicRunArea, Solution* pEscapeSolution);

	bool start();

	void decideBranchNumber();

	~EscapeRunBlock();

	//S)
	
	//E)
};

//S)

//E)

#endif	// ROUTEGUIDE_ESCAPERUNBLOCK_H

//S)

//E)
