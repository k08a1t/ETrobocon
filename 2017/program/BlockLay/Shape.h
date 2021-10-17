// ˅

// ˄

#ifndef SHAPE_H_
#define SHAPE_H_

// ˅
#include "PolygonBlockPlace.h"

// ˄

class Shape
{
	// ˅
	
	// ˄

public:

	int m_ArrangementPosibilityPlace;

	int m_DistanceSum;

	int m_OwnPBPlace;

private:

	PolygonBlockPlace* m_pPBPlace[5];

	Block* m_pBlock[5];

public:

	Shape(PolygonBlockPlace* pPBPlaceA, PolygonBlockPlace* pPBPlaceB, PolygonBlockPlace* pPBPlaceC, PolygonBlockPlace* pPBPlaceD, PolygonBlockPlace* pPBPlaceE);

	void checkCreatedShapeCandidate();

	int getArrangementPosibilityPlace();

	int getDistanceSum();

	int getOwnPBPlace();

	void setPlan(bool pentagon);

	~Shape();

	// ˅
public:
	
protected:
	
private:
	
	// ˄
};

// ˅

// ˄

#endif	// SHAPE_H_

// ˅

// ˄
