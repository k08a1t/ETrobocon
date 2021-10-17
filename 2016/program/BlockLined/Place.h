//S)

//E)

#ifndef BLOCKLINED_PLACE_H
#define BLOCKLINED_PLACE_H

//S)
#include "BlockLined/Block.h"
#include "BlockLined/RouteInfo.h"
//E)

class Place
{
	//S)
	
	//E)

private:

	int m_Distance;

	int m_XCoordinate;

	int m_YCoordinate;

	Block* m_pArrangementBlock;

	Place* m_pAdjoinPlace[4];

	RouteInfo* m_pRouteInfo;

	Block* m_pBlock[4];

public:

	Place(Block* pBlock, int xcoord, RouteInfo* pRouteInfo, Block* pBlockA, Block* pBlockB, Block* pBlockC, Block* pBlockD);

	int getDistance();

	void setDistance(int distance);

	void setDistanceInit(int distance);

	void ResetDistance();

	void addAdjoinPlace(Place* pFrontPlace, Place* pRightPlace, Place* pLeftPlace, Place* pBackPlace);

	void setAdjoinDistance();

	Place* getNextPlace(int list_num);

	int getBackPlace(int bodyDirection);

	bool getArrangeBlockExistence();

	bool getBlockExistence();

	int getBlock();

	~Place();

	int getXcoord();

	void setBlock(int blockNum);

	//S)
	
	//E)
};

//S)

//E)

#endif	// BLOCKLINED_PLACE_H

//S)

//E)
