//S)

//E)

#ifndef ROUTEGUIDE_RUNBLOCK_H
#define ROUTEGUIDE_RUNBLOCK_H

//S)
#include "../Measure/DistanceMeasure.h"
#include "../RunMethod/RunMethod.h"
#include "../Condition/Condition.h"
#include "../Communication/communication.h"
#include "../Mode/Mode.h"

using namespace ev3api;
//E)

class RunBlock
{
	//S)
	
	//E)

protected:

	int m_block_number;

	Condition* m_pCondition;

	DistanceMeasure* m_pDistanceMeasure;

	RunMethod* m_pRunMethod;

	Communication* m_pCommunication;

	Mode* m_pMode;

public:

	virtual bool start();

	RunBlock(int block_number, Condition* pCondition, RunMethod* pRunMethod, DistanceMeasure* pDistanceMeasure, Communication* pCommunication, Mode* pMode);

	int getBlockNumber();

	virtual ~RunBlock();

	//S)
	
	//E)
};

//S)

//E)

#endif	// ROUTEGUIDE_RUNBLOCK_H

//S)

//E)
