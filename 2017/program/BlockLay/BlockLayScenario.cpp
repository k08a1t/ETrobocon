// ˅
#include "Block.h"
#include "BlockLayScenario.h"
#include "Route.h"
#include "Field.h"
// ˄

BlockLayScenario::BlockLayScenario(Route* pRoute, Block* pRedBlock, Block* pYellowBlock, Block* pBlueBlock, Block* pGreenBlock, Block* pBlackBlock)
	// ˅
	:m_RouteSituation(0),m_couse_num(0),m_AmountMovement(0),m_pRoute(pRoute)
	// ˄
{
	// ˅
	m_pBlock[0] = pRedBlock;
	m_pBlock[1] = pYellowBlock;
	m_pBlock[2] = pBlueBlock;
	m_pBlock[3] = pGreenBlock;
	m_pBlock[4] = pBlackBlock;
	// ˄
}

int BlockLayScenario::makeRoute()
{
	// ˅
	//m_AmountMovement = m_pRoute->tranportSearchRoute();//エラーチェック用

	//m_RouteSituationは、0がブロックに向かう(出口に向かう)ルートの確立、1がフィールド内走行、2がブロックを運ぶルートの確立、3がフィールド内走行、4がフィールド内走行

	bool first = true;
	if (first == true) {
		m_pField->decideDiagram();
			first = false;
	}

	if (m_RouteSituation == 0) {
		if (checkFinished() == false) {
			m_AmountMovement = m_pRoute->ObtainSearchRoute();//ブロックに向かうコースを作成させ移動量を受け取る
			m_ObjectBlock = m_pRoute->getTransportBlock();//対象のブロックをメンバに設定
			m_RouteSituation = 1;
		}
		else {
			m_AmountMovement = m_pRoute->EscapeSearchRoute();//出口に向かうルートを作成させ移動量を受け取る
			m_RouteSituation = 4;
		}
	}

	else if (m_RouteSituation == 1) {
		m_couse_num++;
		if (m_couse_num < m_AmountMovement) {//格子繰り返し判定	
		}
		else {
			m_couse_num = 0;
			m_RouteSituation = 2;
		}
	}
	else if (m_RouteSituation == 2) {
			m_AmountMovement = m_pRoute->TransportSearchRoute();//ブロックを置くコースを作成させ移動量を受け取る
			m_RouteSituation = 3;
	}
	else if (m_RouteSituation == 3) {
		m_couse_num++;
		if (m_couse_num < m_AmountMovement) {//格子繰り返し判定	
		}
		else {
			m_couse_num = 0;
			m_RouteSituation = 0;
		}
	}
	else {
		m_couse_num++;
		if (m_couse_num < m_AmountMovement) {//格子繰り返し判定
		}
		else {
			m_couse_num = 0;
			m_RouteSituation = 5;
		}
	}

	return m_RouteSituation;
	// ˄
}

bool BlockLayScenario::checkFinished()
{
	// ˅
	if (m_pBlock[0]->getValidMovementCompleted() == false) {
		return false;
	}
	else if (m_pBlock[1]->getValidMovementCompleted() == false) {
		return false;
	}
	else if (m_pBlock[2]->getValidMovementCompleted() == false) {
		return false;
	}
	else if (m_pBlock[3]->getValidMovementCompleted() == false) {
		return false;
	}
	else if (m_pBlock[4]->getValidMovementCompleted() == false) {
		return false;
	}
	else {
		return true;
	}
	// ˄
}

int BlockLayScenario::getCouse()
{
	// ˅
	int value = m_pRoute->getProsess(m_couse_num);
	return value;
	// ˄
}

BlockLayScenario::~BlockLayScenario()
{
	// ˅
	
	// ˄
}

// ˅

// ˄
