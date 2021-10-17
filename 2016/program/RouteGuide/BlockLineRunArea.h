//S)

//E)

#ifndef ROUTEGUIDE_BLOCKLINERUNAREA_H
#define ROUTEGUIDE_BLOCKLINERUNAREA_H

//S)
#include "RouteGuide/RunArea.h"
#include "BlockLined/Solution.h"

using namespace ev3api;
//E)

class BlockLineRunArea : public RunArea
{
	//S)
	
	//E)

private:

	int m_list_num;

	bool m_finish;

	bool m_first;

	RunArea* m_pBLRunArea[3];

	Solution* m_pSolution;

public:

	BlockLineRunArea(RunArea* pCross, RunArea* pSetting, RunArea* plook, Solution* pSolution);

	bool start();

private:

	void judgeBLArea();

public:

	~BlockLineRunArea();

	//S)
	
	//E)
};

//S)

//E)

#endif	// ROUTEGUIDE_BLOCKLINERUNAREA_H

//S)

//E)
