//S)

//E)

#ifndef ROUTEGUIDE_ROUTESEARCHRUNBLOCK_H
#define ROUTEGUIDE_ROUTESEARCHRUNBLOCK_H

//S)
#include "RouteGuide/Runblock.h"
#include "RouteGuide/DynamicRunArea.h"

using namespace ev3api;
//E)

class RouteSearchRunBlock : public RunBlock
{
	//S)
	
	//E)

protected:

	DynamicRunArea* m_pDynamicRunArea;

public:

	RouteSearchRunBlock(int block_number, Condition* pCondition, RunMethod* pRunMethod, DistanceMeasure* pDistanceMeasure, Communication* pCommunication, Mode* pMode, DynamicRunArea* pDynamicRunArea);

	virtual bool start() = 0;

private:

	virtual void decideBranchNumber() = 0;

public:

	virtual ~RouteSearchRunBlock();

	//S)
	
	//E)
};

//S)

//E)

#endif	// ROUTEGUIDE_ROUTESEARCHRUNBLOCK_H

//S)

//E)
