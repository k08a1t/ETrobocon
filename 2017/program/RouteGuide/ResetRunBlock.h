//S)

//E)

#ifndef ROUTEGUIDE_RESETRUNBLOCK_H
#define ROUTEGUIDE_RESETRUNBLOCK_H

//S)
#include "RouteGuide/Runblock.h"

using namespace ev3api;
//E)

class ResetRunBlock : public RunBlock
{
	//S)
	
	//E)

public:

	bool start();

	ResetRunBlock(int block_number, Condition* pCondition, RunMethod* pRunMethod, DistanceMeasure* pDistanceMeasure, Communication* pCommunication, Mode* pMode);

	~ResetRunBlock();

	//S)
	
	//E)
};

//S)

//E)

#endif	// ROUTEGUIDE_RESETRUNBLOCK_H

//S)

//E)
