// ˅
#include "CenterBlockPlace.h"
#include "BlockPlace.h"
#include "Block.h"
// ˄

CenterBlockPlace::CenterBlockPlace(int PlaceNumber, int distance0, int distance1, int distance2, int distance3, int distance4, int distance5, int distance6, int distance7, int distance8, int distance9, int distance10, int distance11, int distance12, int distance13, int distance14, int distance15)
	// ˅
	
	// ˄
{
	// ˅
	m_DistanceData[0] = distance0;
	m_DistanceData[1] = distance1;
	m_DistanceData[2] = distance2;
	m_DistanceData[3] = distance3;
	m_DistanceData[4] = distance4;
	m_DistanceData[5] = distance5;
	m_DistanceData[6] = distance6;
	m_DistanceData[7] = distance7;
	m_DistanceData[8] = distance8;
	m_DistanceData[9] = distance9;
	m_DistanceData[10] = distance10;
	m_DistanceData[11] = distance11;
	m_DistanceData[12] = distance12;
	m_DistanceData[13] = distance13;
	m_DistanceData[14] = distance14;
	m_DistanceData[15] = distance15;
	// ˄
}

void CenterBlockPlace::setArrangementPlan(Block* block)
{
	// ˅
	m_ArrangementPlan = block;
	// ˄
}

int CenterBlockPlace::getDistance()
{
	// ˅
	return m_Distance;
	// ˄
}

int CenterBlockPlace::getPlaceNumber()
{
	// ˅
	return m_PlaceNumber;
	// ˄
}

Block* CenterBlockPlace::getArrangementPlan()
{
	// ˅
	return m_ArrangementPlan;
	// ˄
}

int CenterBlockPlace::getDistanceData(int AnotherPlaceNumber)
{
	// ˅
	return m_DistanceData[AnotherPlaceNumber];
	// ˄
}

CenterBlockPlace::~CenterBlockPlace()
{
	// ˅
	
	// ˄
}

// ˅

// ˄
