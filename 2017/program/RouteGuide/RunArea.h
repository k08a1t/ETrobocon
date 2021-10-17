//S)

//E)

#ifndef ROUTEGUIDE_RUNAREA_H
#define ROUTEGUIDE_RUNAREA_H

//S)
#include "RouteGuide/Runblock.h"

using namespace ev3api;
//E)

class RunArea
{
	//S)
	
	//E)

protected:

	int m_list_num;

	int m_current_index;

	RunBlock* m_pRunBlock_list[70];

	RunBlock* m_pRunBlock;

public:

	virtual bool start();

	void addBlock(RunBlock* pBlock);

	RunArea();

	virtual ~RunArea();

	//S)
	
	//E)
};

//S)

//E)

#endif	// ROUTEGUIDE_RUNAREA_H

//S)

//E)
