// ˅
#include "BlackLine.h"
#include "PolygonBlockPlace.h"
#include "Color.h"
#include "Angle.h"
using namespace std;
// ˄

PolygonBlockPlace::PolygonBlockPlace(int PlaceNumber, int distance0, int distance1, int distance2, int distance3, int distance4, int distance5, int distance6, int distance7, int distance8, int distance9, int distance10, int distance11, int distance12, int distance13, int distance14, int distance15, BlackLine* Line1, BlackLine* Line2, BlackLine* Line3, BlackLine* Line4, Color PlaceColor)
	// ˅
	:m_Color(PlaceColor), m_PassedLine(0),m_PlaceNumber(PlaceNumber), m_pArrangementBlock(nullptr)
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

	m_pConnectBlackLine[0] = Line1;
	m_pConnectBlackLine[1] = Line2;
	m_pConnectBlackLine[2] = Line3;
	m_pConnectBlackLine[3] = Line4;

	// ˄
}

void PolygonBlockPlace::setDistance(int distance)
{
	// ˅
	m_Distance = distance;
	// ˄
}

void PolygonBlockPlace::setAdjoinDistance(bool blackblock)
{
	// ˅
	for (int i = 0;i < 4;i++) {
		if (m_pConnectBlackLine[i] != nullptr) {//黒線がある
			if (m_pConnectBlackLine[i]->getDistance() > m_Distance + 1) {//自分の道のり+1よりも値が大きい
				m_pConnectBlackLine[i]->setDistance(m_Distance + 1);//自分の道のり+1を入れる
				if (blackblock == false) {
					m_pConnectBlackLine[i]->setAdjoinDistance(false);
				}
				else {
					m_pConnectBlackLine[i]->setAdjoinDistance(true);
				}
			}
		}
	}
	// ˄
}

void PolygonBlockPlace::setDistancefromBB(int distance)
{
	// ˅
	m_DistancefromBB = distance;
	// ˄
}

void PolygonBlockPlace::setDistancefromSCB()
{
	// ˅
	m_DistancefromSCB = m_Distance;
	// ˄
}

void PolygonBlockPlace::setUseDistancefromBB()
{
	// ˅
	m_UseDistancefromBB = true;
	// ˄
}

void PolygonBlockPlace::setBlock(Block* block)
{
	// ˅
	m_pArrangementBlock = block;
	// ˄
}

void PolygonBlockPlace::setArrangementPlan(Block* block)
{
	// ˅
	m_ArrangementPlan = block;
	// ˄
}

void PolygonBlockPlace::resetDistance()
{
	// ˅
	m_Distance = 100;
	// ˄
}

int PolygonBlockPlace::getDistance()
{
	// ˅
	return m_Distance;
	// ˄
}

int PolygonBlockPlace::getDistancefromBB()
{
	// ˅
	return m_DistancefromBB;
	// ˄
}

int PolygonBlockPlace::getDistancefromSCB()
{
	// ˅
	return m_DistancefromSCB;
	// ˄
}

bool PolygonBlockPlace::getUseDistancefromBB()
{
	// ˅
	return m_UseDistancefromBB;
	// ˄
}

Block* PolygonBlockPlace::getBlock()
{
	// ˅
	return m_pArrangementBlock;
	// ˄
}

Color PolygonBlockPlace::getPlaceColor()
{
	// ˅
	return m_Color;
	// ˄
}

int PolygonBlockPlace::getDistanceData(int AnotherPlaceNumber)
{
	// ˅
	return m_DistanceData[AnotherPlaceNumber];
	// ˄
}

int PolygonBlockPlace::getPlaceNumber()
{
	// ˅
	return m_PlaceNumber;
	// ˄
}

Block* PolygonBlockPlace::getArrangementPlan()
{
	// ˅
	return m_ArrangementPlan;
	// ˄
}

PolygonBlockPlace* PolygonBlockPlace::getNextPlace(int list_num, unsigned short type)
{
	// ˅
	int NextLine = 100;
	PolygonBlockPlace* NextPlace = nullptr;
	
	for (int i = 0;i < 4;i++) {//接続している黒線
		if (m_pConnectBlackLine[i] != nullptr) {//黒線がある
			if (m_Distance - 1 == m_pConnectBlackLine[i]->getDistance()) {//繋がっている黒線の道のりが今いる置き場の道のり-1
				if (NextLine >= m_pConnectBlackLine[i]->getLineNumber()) {
					NextLine = m_pConnectBlackLine[i]->getLineNumber();//黒線番号が最小のものを設定
				}
				NextPlace = m_pConnectBlackLine[i]->getAnotherPBPlace(m_PlaceNumber);
			}
		}
	}
	int Angle = 0;
	if (type == 0) {
		Angle = m_pAngle->getAngle(m_PassedLine, NextLine);//今の黒線と置き場の後に通る黒線
	}
	else if(type == 1 || type == 2){//escape用
		Angle = m_pAngle->getAngle(m_PassedLine, 23);
	}
	else if (type == 3) {
		Angle = 17;
	}
	else if(type == 4){
		Angle = 18;
	}
	else if (type == 5) {
		Angle = 19;
	}
	m_PassedLine = NextLine;

	switch (Angle)
	{
	case 0://0°
		if (getBlock() != nullptr) {
			m_pAffiliationRoute->setProsess(list_num, 0);
		}
		else {
			m_pAffiliationRoute->setProsess(list_num, 35373901);
		}
		break;
	case 1://30°
		if (getBlock() != nullptr) {
			m_pAffiliationRoute->setProsess(list_num, 343902);
		}
		else {
			m_pAffiliationRoute->setProsess(list_num, 35373903);
		}
		break;
	case 2://-30°
		if (getBlock() != nullptr) {
			m_pAffiliationRoute->setProsess(list_num, 343804);
		}
		else {
			m_pAffiliationRoute->setProsess(list_num, 35363805);
		}
		break;
	case 3://45°
		if (getBlock() != nullptr) {
			m_pAffiliationRoute->setProsess(list_num, 343906);
		}
		else {
			m_pAffiliationRoute->setProsess(list_num, 35373907);
		}
		break;
	case 4://-45°
		if (getBlock() != nullptr) {
			m_pAffiliationRoute->setProsess(list_num, 343808);
		}
		else {
			m_pAffiliationRoute->setProsess(list_num, 35363809);
		}
		break;
	case 5://60°
		if (getBlock() != nullptr) {
			m_pAffiliationRoute->setProsess(list_num, 343910);
		}
		else {
			m_pAffiliationRoute->setProsess(list_num, 35373911);
		}
		break;
	case 6://-60°
		if (getBlock() != nullptr) {
			m_pAffiliationRoute->setProsess(list_num, 343812);
		}
		else {
			m_pAffiliationRoute->setProsess(list_num, 35363813);
		}
		break;
	case 7://90°
		if (getBlock() != nullptr) {
			m_pAffiliationRoute->setProsess(list_num, 343914);
		}
		else {
			m_pAffiliationRoute->setProsess(list_num, 35373915);
		}
		break;
	case 8://-90°
		if (getBlock() != nullptr) {
			m_pAffiliationRoute->setProsess(list_num, 343816);
		}
		else {
			m_pAffiliationRoute->setProsess(list_num, 35363817);
		}
		break;
	case 9://105°
		if (getBlock() != nullptr) {
			m_pAffiliationRoute->setProsess(list_num, 343918);
		}
		else {
			m_pAffiliationRoute->setProsess(list_num, 35373919);
		}
		break;
	case 10://-105°
		if (getBlock() != nullptr) {
			m_pAffiliationRoute->setProsess(list_num, 343820);
		}
		else {
			m_pAffiliationRoute->setProsess(list_num, 35363821);
		}
		break;
	case 11://120°
		if (getBlock() != nullptr) {
			m_pAffiliationRoute->setProsess(list_num, 343922);
		}
		else {
			m_pAffiliationRoute->setProsess(list_num, 35373923);
		}
		break;
	case 12://-120°
		if (getBlock() != nullptr) {
			m_pAffiliationRoute->setProsess(list_num, 343824);
		}
		else {
			m_pAffiliationRoute->setProsess(list_num, 35363825);
		}
		break;
	case 13://135°
		if (getBlock() != nullptr) {
			m_pAffiliationRoute->setProsess(list_num, 343926);
		}
		else {
			m_pAffiliationRoute->setProsess(list_num, 35373927);
		}
		break;
	case 14://-135°
		if (getBlock() != nullptr) {
			m_pAffiliationRoute->setProsess(list_num, 343828);
		}
		else {
			m_pAffiliationRoute->setProsess(list_num, 35363829);
		}
		break;
	case 15://150°
		if (getBlock() != nullptr) {
			m_pAffiliationRoute->setProsess(list_num, 343930);
		}
		else {
			m_pAffiliationRoute->setProsess(list_num, 353739);
		}
		break;
	case 16://-150°
		if (getBlock() != nullptr) {
			m_pAffiliationRoute->setProsess(list_num, 343832);
		}
		else {
			m_pAffiliationRoute->setProsess(list_num, 353638);
		}
		break;
	case 17://type=3,置き場4を通過するとき
		m_pAffiliationRoute->setProsess(list_num, 1635);
		break;
	case 18://type=4,置き場11を通過するとき
		m_pAffiliationRoute->setProsess(list_num, 1435);
		break;
	case 19:
		m_pAffiliationRoute->setProsess(list_num, 40);
		break;
	}
	return NextPlace;
	// ˄
}

PolygonBlockPlace::~PolygonBlockPlace()
{
	// ˅
	
	// ˄
}

// ˅

// ˄
