// ˅
#include "PolygonBlockPlace.h"
#include "Block.h"
#include "Shape.h"

// ˄

Shape::Shape(PolygonBlockPlace* pPBPlaceA, PolygonBlockPlace* pPBPlaceB, PolygonBlockPlace* pPBPlaceC, PolygonBlockPlace* pPBPlaceD, PolygonBlockPlace* pPBPlaceE)
	// ˅
	
	// ˄
{
	// ˅
	m_pPBPlace[0] = pPBPlaceA;
	m_pPBPlace[1] = pPBPlaceB;
	m_pPBPlace[2] = pPBPlaceC;
	m_pPBPlace[3] = pPBPlaceD;
	m_pPBPlace[4] = pPBPlaceE;

	for (int i = 0;i < 5;i++) {
		if (m_pPBPlace[i] != nullptr) {
			m_OwnPBPlace++;
		}
	}
	// ˄
}

void Shape::checkCreatedShapeCandidate()
{
	// ˅
	for (int i = 0;i < 5;i++) {
		if (m_pPBPlace[i] != nullptr) {//置き場がある
			if (m_pPBPlace[i]->getDistancefromSCB() == 2 || m_pPBPlace[i]->getDistancefromSCB() == 4) {//同色ブロックからの道のりが2か4
				m_ArrangementPosibilityPlace++;//配置可能置き場数+1
				m_DistanceSum += m_pPBPlace[i]->getDistancefromSCB();//道のり合計に同色ブロックからの道のりを足す
			}
		}
	}

	// ˄
}

int Shape::getArrangementPosibilityPlace()
{
	// ˅
	return m_ArrangementPosibilityPlace;
	// ˄
}

int Shape::getDistanceSum()
{
	// ˅
	return m_DistanceSum;
	// ˄
}

int Shape::getOwnPBPlace()
{
	// ˅
	return m_OwnPBPlace;
	// ˄
}

void Shape::setPlan(bool pentagon)
{
	// ˅
		for (int i = 0;i < 5;i++) {//置き場
			for (int j = 0;j < 5;j++) {//ブロック
				if (pentagon == false) {
					if (m_pPBPlace[i]->getPlaceColor() == m_pBlock[j]->getBlockColor()) {//色が置き場と同じ色
						m_pPBPlace[i]->setArrangementPlan(m_pBlock[j]);//配置予定を設定
						m_pBlock[j]->setUseDiagram();
					}
				}
				else {
					if (m_pPBPlace[i]->getPlaceColor() == 5 && m_pPBPlace[i]->getDistancefromBB() >= m_pPBPlace[i]->getDistancefromSCB()) {//置き場の色が赤かつ黒からの道のりより同色からの道のりが小さい
						if (m_pPBPlace[i]->getPlaceColor() == m_pBlock[j]->getBlockColor()) {//色が置き場と同じ色
							m_pPBPlace[i]->setArrangementPlan(m_pBlock[j]);//配置予定を設定
							m_pBlock[j]->setUseDiagram();
						}
					}
					else if (m_pPBPlace[i]->getPlaceColor() == 5 && m_pPBPlace[i]->getDistancefromBB() < m_pPBPlace[i]->getDistancefromSCB()) {
						m_pPBPlace[i]->getUseDistancefromBB();
						if (m_pBlock[j]->getBlockColor() == 1) {
							m_pPBPlace[i]->setArrangementPlan(m_pBlock[j]);//配置予定を設定
							m_pBlock[j]->setUseDiagram();
						}
					}
				}
			}
		}
	// ˄
}

Shape::~Shape()
{
	// ˅
	
	// ˄
}

// ˅

// ˄
