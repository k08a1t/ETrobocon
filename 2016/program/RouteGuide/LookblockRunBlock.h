//S)

//E)

#ifndef ROUTEGUIDE_LOOKBLOCKRUNBLOCK_H
#define ROUTEGUIDE_LOOKBLOCKRUNBLOCK_H

//S)
#include "RouteGuide/Runblock.h"
#include "BlockLined/Solution.h"

using namespace ev3api;
//E)

class LookblockRunBlock : public RunBlock
{
	//S)
	
	//E)

private:

	Solution* m_pLookSolution;

public:

	bool start();

	LookblockRunBlock(int block_number, Condition* pCondition, RunMethod* pRunMethod, DistanceMeasure* pDistanceMeasure, Communication* pCommunication, Mode* pMode, Solution* pSolution);

	~LookblockRunBlock();

	//S)
	
	//E)
};

//S)

//E)

#endif	// ROUTEGUIDE_LOOKBLOCKRUNBLOCK_H

//S)

//E)
