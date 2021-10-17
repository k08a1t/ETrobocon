// ˅

// ˄

#ifndef POLYGONBLOCKPLACE_H_
#define POLYGONBLOCKPLACE_H_

// ˅
class Angle;
class BlackLine;
class Block;
#include "Route.h"
#include "Color.h"
// ˄

class PolygonBlockPlace
{
	// ˅
	
	// ˄

private:

	Color m_Color;

	int m_DistancefromSCB;

	int m_PassedLine;

	int m_Distance;

	int m_DistanceData[16];

	int m_PlaceNumber;

	Block* m_ArrangementPlan;

	int m_DistancefromBB;

	bool m_UseDistancefromBB;

	Block* m_pArrangementBlock;

	BlackLine* m_pConnectBlackLine[4];

	Route* m_pAffiliationRoute;

	Angle* m_pAngle;

public:

	PolygonBlockPlace(int PlaceNumber, int distance0, int distance1, int distance2, int distance3, int distance4, int distance5, int distance6, int distance7, int distance8, int distance9, int distance10, int distance11, int distance12, int distance13, int distance14, int distance15, BlackLine* Line1, BlackLine* Line2, BlackLine* Line3, BlackLine* Line4, Color PlaceColor);

	void setDistance(int distance);

	void setAdjoinDistance(bool blackblock);

	void setDistancefromBB(int distance);

	void setDistancefromSCB();

	void setUseDistancefromBB();

	void setBlock(Block* block);

	void setArrangementPlan(Block* block);

	void resetDistance();

	int getDistance();

	int getDistancefromBB();

	int getDistancefromSCB();

	bool getUseDistancefromBB();

	Block* getBlock();

	Color getPlaceColor();

	int getDistanceData(int AnotherPlaceNumber);

	int getPlaceNumber();

	Block* getArrangementPlan();

	PolygonBlockPlace* getNextPlace(int list_num, unsigned short type);

	~PolygonBlockPlace();

	// ˅
public:
	
protected:
	
private:
	
	// ˄
};

// ˅

// ˄

#endif	// POLYGONBLOCKPLACE_H_

// ˅

// ˄
