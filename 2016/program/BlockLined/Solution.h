//S)

//E)

#ifndef BLOCKLINED_SOLUTION_H
#define BLOCKLINED_SOLUTION_H

//S)
#include "BlockLined/Route.h"
#include "BlockLined/Block.h"
#include "BlockLined/MovementType.h"

//E)

class Solution
{
	//S)
	
	//E)

private:

	int m_RouteSituation;

	Block* m_PurposeBlock;

	int m_AmountMovement;

	int m_couse_num;

	int m_transport_count;

	Route* m_pRoute;

	Block* m_pBlock[4];

public:

	Solution(Route* pRoute, Block* pBlockA, Block* pBlockB, Block* pBlockC, Block* pBlockD);

	int makeSolution();

private:

	bool checkFinished();

public:

	void searchBlockcolor();

	int getCourse();

	int getEscapeDirecrion();

	~Solution();

	void LCDout();

	//S)
	
	//E)
};

//S)

//E)

#endif	// BLOCKLINED_SOLUTION_H

//S)

//E)
