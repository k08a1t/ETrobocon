// ˅
#include "Angle.h"
#include "BlackLine.h"
#include "PolygonBlockPlace.h"

// ˄

BlackLine::BlackLine(int line_num)
	// ˅

	// ˄
{
	// ˅
	
	// ˄
}

int BlackLine::getLineNumber()
{
	// ˅
	return m_LineNumber;
	// ˄
}

void BlackLine::setAdjoinDistance(bool blackblock)
{
	// ˅
	if (blackblock == false) {
		for (int i = 0;i < 2;i++) {
			if (m_pConnectPBPlace[i]->getDistance() > m_Distance + 1) {//自分の道のり+1よりも道のりが大きい
				m_pConnectPBPlace[i]->setDistance(m_Distance + 1);//自分の道のり+1を設定する
			}
		}
	}
	else {
		for (int i = 0;i < 2;i++) {
			if (m_pConnectPBPlace[i]->getDistancefromBB() > m_Distance + 1) {//自分の道のり+1よりも道のりが大きい
				m_pConnectPBPlace[i]->setDistancefromBB(m_Distance + 1);//自分の道のり+1を設定する
			}
		}
	}
	// ˄
}

void BlackLine::setDistance(int distance)
{
	// ˅
	m_Distance = distance;
	// ˄
}

PolygonBlockPlace* BlackLine::getAnotherPBPlace(int PBPlaceNumber)
{
	// ˅
	PolygonBlockPlace* AnotherPBPlace = nullptr;
	
	for (int i = 0;i < 2;i++) {
		if (m_pConnectPBPlace[i]->getPlaceNumber() != PBPlaceNumber) {
			AnotherPBPlace = m_pConnectPBPlace[i];
		}
	}

	return AnotherPBPlace;
	// ˄
}

int BlackLine::getDistance()
{
	// ˅
	return m_Distance;
	// ˄
}

BlackLine::~BlackLine()
{
	// ˅
	
	// ˄
}

// ˅

// ˄
