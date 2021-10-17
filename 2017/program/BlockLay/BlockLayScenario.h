// ˅

// ˄

#ifndef BLOCKLAYSCENARIO_H_
#define BLOCKLAYSCENARIO_H_

// ˅
class Block;
class PolygonBlockPlace;
class Route;
class Field;
// ˄

class BlockLayScenario
{
	// ˅
	
	// ˄

private:

	int m_RouteSituation;

public:

	int m_couse_num;

private:

	int m_AmountMovement;

	Block* m_ObjectBlock;

	Block* m_pBlock[5];

	Route* m_pRoute;

	Field* m_pField;

public:

	BlockLayScenario(Route* pRoute, Block* pRedBlock, Block* pYellowBlock, Block* pBlueBlock, Block* pGreenBlock, Block* pBlackBlock);

	int makeRoute();

	bool checkFinished();

	int getCouse();

	~BlockLayScenario();

	// ˅
public:
	
protected:
	
private:
	
	// ˄
};

// ˅

// ˄

#endif	// BLOCKLAYSCENARIO_H_

// ˅

// ˄
