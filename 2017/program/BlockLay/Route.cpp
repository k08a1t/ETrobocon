// ˅
#include "Block.h"
#include "Field.h"
#include "PolygonBlockPlace.h"
#include "Route.h"

// ˄

Route::Route(Field* pField)
	// ˅
	: m_ViaNod(0), m_pField(pField),m_pTransportBlock(nullptr)
	// ˄
{
	// ˅
	m_Process[0] = 0;
	m_Process[1] = 0;
	m_Process[2] = 0;
	m_Process[3] = 0;
	m_Process[4] = 0;
	m_Process[5] = 0;
	m_Process[6] = 0;
	m_Process[7] = 0;
	m_Process[8] = 0;
	m_Process[9] = 0;
	m_Process[10] = 0;
	m_Process[11] = 0;
	m_Process[12] = 0;
	m_Process[13] = 0;
	m_Process[14] = 0;
	m_Process[15] = 0;
	m_Process[16] = 0;
	m_Process[17] = 0;
	m_Process[18] = 0;
	m_Process[19] = 0;
	// ˄
}

int Route::ObtainSearchRoute()
{
	// ˅
	int StartPoint = m_pField->getPresentPoint();//現在地取得

	int GoalPoint = m_pField->JudgementClosestBlock();//最寄りブロック判定

	m_pTransportBlock = m_pThroughPBPlace[GoalPoint]->getBlock();//対象のブロック設定

	m_pField->makeDistanceList(GoalPoint,false);//道のり一覧作成

	m_ViaNod = m_pThroughPBPlace[StartPoint]->getDistance() - 1;//通過ノード数

	m_ViaPoint[0] = m_pThroughPBPlace[StartPoint]->getNextPlace(0, 0);//通過する置き場

	for (int i = 0; i < m_ViaNod;i++) {					
		m_ViaPoint[i + 1] = m_ViaPoint[i]->getNextPlace(i + 1, 0);
	}

	m_pField->renewalPresentPoint(GoalPoint);//現在地更新

	return m_ViaNod + 1;
	// ˄
}

Block* Route::getTransportBlock()
{
	// ˅
	return m_pTransportBlock;
	// ˄
}

int Route::getProsess(int num)
{
	// ˅
	return m_Process[num];
	// ˄
}

int Route::TransportSearchRoute()
{
	// ˅
	int StartPoint = m_pField->getPresentPoint();

	int GoalPoint = 0;
	for (int i = 0;i < 16;i++) {
		if (m_pThroughPBPlace[i]->getArrangementPlan() == m_pTransportBlock) {//現在運搬ブロックが配置予定になっている置き場
			GoalPoint = i;
		}
	}

	m_pField->makeDistanceList(GoalPoint,false);//道のり一覧作成
	
	m_ViaNod = m_pThroughPBPlace[StartPoint]->getDistance() - 1;//通過ノード数

	m_pThroughPBPlace[StartPoint]->setBlock(nullptr);//ルートの開始する置き場にあるブロックをなくす。

	m_ViaPoint[0] = m_pThroughPBPlace[StartPoint]->getNextPlace(0, 0);//通過する置き場

	for (int i = 0; i< m_ViaNod;i++) {						
		m_ViaPoint[i + 1] = m_ViaPoint[i]->getNextPlace(i + 1, 0);
	}
	m_ViaPoint[m_ViaNod + 1] = m_ViaPoint[m_ViaNod]->getNextPlace(m_ViaNod + 1, 5);//置く動きをさせる
	

	m_pThroughPBPlace[GoalPoint]->setBlock(m_pTransportBlock);//開始の置き場からなくしたブロックを配置する

	m_pTransportBlock->setValidMovementComplete();//ブロックを配置済にする

	int Presentpoint = m_ViaPoint[m_ViaNod - 1]->getPlaceNumber();//目的地のひとつ前の置き場

	m_pField->renewalPresentPoint(Presentpoint);//現在地更新

	return m_ViaNod + 1;
	// ˄
}

int Route::EscapeSearchRoute()
{
	// ˅
	int StartPoint = m_pField->getPresentPoint();//現在地取得

	int GoalPoint = 0;
	int Distance = 100;
	int type = 0;

	m_pField->makeDistanceList(StartPoint,false);//4の置き場と11の置き場の道のりを比べるため

	for (int i = 0;i < 15;i++) {
		if (m_pThroughPBPlace[i]->getPlaceNumber() == 4 || m_pThroughPBPlace[i]->getPlaceNumber() == 11) {//4か11の置き場
			if (m_pThroughPBPlace[i]->getPlaceNumber() == 4) {//4の置き場
				type = 1;
			}
			else {//11の置き場
				type = 2;
			}
			if (Distance >= m_pThroughPBPlace[i]->getDistance()) {//4か11の置き場の道のりの短い方を設定
				Distance = m_pThroughPBPlace[i]->getDistance();
				GoalPoint = i;
			}
		}
	}

	m_pField->makeDistanceList(GoalPoint,false);//道のり一覧作成

	m_ViaNod = m_pThroughPBPlace[StartPoint]->getDistance() - 1;//通過ノード数

	m_ViaPoint[0] = m_pThroughPBPlace[StartPoint]->getNextPlace(0, 0);

	for (int i = 0; i< m_ViaNod;i++) {
		m_ViaPoint[i + 1] = m_ViaPoint[i]->getNextPlace(i + 1, 0);//processを設定,最後のm_ViaPointには目的地が入る,最後のprocessには目的地に向かう角度の動きが入る
	}
	if (type != 0) {//escapeの時
		m_ViaPoint[m_ViaNod + 1] = m_ViaPoint[m_ViaNod]->getNextPlace(m_ViaNod + 1, type);//目的地(4か11の置き場)から黒線23への角度,黒線23の間の置き場17を入れる
		if (type == 1) {
			type = 3;
		}
		else if (type == 2) {
			type = 4;
		}
		m_ViaPoint[m_ViaNod + 2] = m_ViaPoint[m_ViaNod + 1]->getNextPlace(m_ViaNod + 2, type);//ゲームエリアを抜けた先の線の置き場18を入れる
	}

	m_pField->renewalPresentPoint(GoalPoint);//現在地更新

	return m_ViaNod + 1;
	// ˄
}

void Route::setProsess(int num, int acceed)
{
	// ˅
	m_Process[num] = acceed;
	// ˄
}

Route::~Route()
{
	// ˅
	
	// ˄
}

// ˅

// ˄
