//S)

//E)

#ifndef ROUTEGUIDE_DYNAMICRUNAREA_H
#define ROUTEGUIDE_DYNAMICRUNAREA_H

//S)
#include "RouteGuide/RunArea.h"

using namespace ev3api;
//E)

class DynamicRunArea : public RunArea
{
	//S)
	
	//E)

private:

	int m_branch_number[4];

public:

	bool start();

	void setBranchNumber(int branch_num);

private:

	bool judgeRunBlock();

public:

	DynamicRunArea();

	~DynamicRunArea();

	//S)
	
	//E)
};

//S)

//E)

#endif	// ROUTEGUIDE_DYNAMICRUNAREA_H

//S)

//E)
