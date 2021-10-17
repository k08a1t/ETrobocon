// ˅
#include "BlackLine.h"
#include "Block.h"
#include "Field.h"
#include "Shape.h"
#include "PolygonBlockPlace.h"
// ˄

Field::Field(int pPresentPoint, Block* pRedBlock, Block* pYellowBlock, Block* pBlueBlock, Block* pGreenBlock, Block* pBlackBlock)
	// ˅
:m_PresentPoint(pPresentPoint)
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

void Field::convertEPcode(int epcode)
{
	// ˅
	int Blackblock = 0, Redblock = 0, Yellowblock = 0, Blueblock = 0, Greenblock = 14;//Greenに値を入れる
	int sum = 0;

	m_EPcode = epcode;

	for (int a = 0;a < 15;a++) {
		for (int b = 0;b < 11;b++) {
			for (int c = 0;c < 11;c++) {
				for (int d = 0;d < 11;d++) {
					sum = 1331 * a + 121 * b + 11 * c + d;
					if (sum == m_EPcode) {
						Blackblock = a + 1, Redblock = b + 1, Yellowblock = c + 1, Blueblock = d + 1;
					}
				}
			}
		}
	}

	m_pPBPlace[Redblock]->setBlock(m_pBlock[0]);
	m_pPBPlace[Yellowblock]->setBlock(m_pBlock[1]);
	m_pPBPlace[Blueblock]->setBlock(m_pBlock[2]);
	m_pPBPlace[Greenblock]->setBlock(m_pBlock[3]);
	m_pPBPlace[Blackblock]->setBlock(m_pBlock[4]);

	// ˄
}

int Field::getPresentPoint()
{
	// ˅
	return m_pPBPlace[m_PresentPoint]->getPlaceNumber();
	// ˄
}

void Field::makeDistanceList(int StartPlaceNumber, bool blackblock)
{
	// ˅
	//全置き場リセット
	for (int i = 0;i < 15;i++) {
		m_pPBPlace[i]->resetDistance();
	}
	//起点0リセット
	m_pPBPlace[StartPlaceNumber]->setDistance(0);

	for (int i = 0;i < 15;i++) {
		if (blackblock == false) {
			m_pPBPlace[i]->setAdjoinDistance(false);
		}
		else {
			m_pPBPlace[i]->setAdjoinDistance(true);
		}
	}

	// ˄
}

void Field::makeDistancefromSCBList()
{
	// ˅
	//同色ブロックからの道のり一覧作成
	for (int i = 0;i < 15;i++) {//置き場
		if (m_pPBPlace[i]->getBlock() != nullptr) {
			makeDistanceList(i,false);
			for (int j = 0;j < 15;j++) {
				if (m_pBlock[i]->getBlockColor() == m_pPBPlace[j]->getPlaceColor()) {
					m_pPBPlace[j]->setDistancefromSCB();
				}
			}
		}
	}

	//黒ブロックからの道のり一覧作成
	for (int i = 0;i < 15;i++) {
		if ((m_pPBPlace[i]->getBlock())->getBlockColor() == 1) {
			int BlackBlock = m_pPBPlace[i]->getPlaceNumber();
			makeDistanceList(BlackBlock, true);
		}
	}


	// ˄
}

int Field::JudgementClosestBlock()
{
	// ˅
	//道のり一覧の作成
	int start = m_pPBPlace[m_PresentPoint]->getPlaceNumber();
	makeDistanceList(start,false);

	//現在地点から最も近いブロックの判定
	int Distance = 100;
	int BlockPlaceNumber = 100;


	for (int i = 0;i < 15;i++) {
		if (m_CreatePentagon == false) {//五角形以外
			if (m_pPBPlace[i]->getBlock() != nullptr) {
				if ((m_pPBPlace[i]->getBlock())->getBlockColor() != 1) {
					if (m_pPBPlace[i]->getDistance() < Distance && (m_pPBPlace[i]->getBlock())->getValidMovementCompleted() == false) {
						Distance = m_pPBPlace[i]->getDistance();
						BlockPlaceNumber = i;
					}
					else if (m_pPBPlace[i]->getDistance() == Distance && (m_pPBPlace[i]->getBlock())->getValidMovementCompleted() == false) {
						if (m_pPBPlace[i]->getPlaceNumber() < BlockPlaceNumber) {//置き場番号小さい方優先
							BlockPlaceNumber = i;
						}
					}
				}
			}
		}
	}

	for (int i = 0;i < 15;i++) {
		if (m_CreatePentagon == true) {//五角形
			if (m_pPBPlace[i]->getBlock() != nullptr) {
				if (m_pPBPlace[i]->getDistance() < Distance && (m_pPBPlace[i]->getBlock())->getValidMovementCompleted() == false) {
					Distance = m_pPBPlace[i]->getDistance();
					BlockPlaceNumber = i;
				}
				else if (m_pPBPlace[i]->getDistance() == Distance && (m_pPBPlace[i]->getBlock())->getValidMovementCompleted() == false) {
					if (m_pPBPlace[i]->getPlaceNumber() < BlockPlaceNumber) {//置き場番号小さい方優先
							BlockPlaceNumber = i;
					}
				}
			}
		}
	}
	return BlockPlaceNumber;
	// ˄
}

void Field::renewalPresentPoint(int NewPresentPoint)
{
	// ˅
	m_PresentPoint = NewPresentPoint;
	// ˄
}

void Field::decideDiagram()
{
	// ˅
	Shape* decideShape = nullptr;

	for (int i = 0;i < 14;i++) {
		m_pShape[i]->checkCreatedShapeCandidate();
	}
	for (int i = 0;i < 14;i++) {
		if (m_pShape[i]->getArrangementPosibilityPlace() >= m_pShape[i]->getOwnPBPlace() - 1) {
			if (m_pShape[i]->getOwnPBPlace() == 5) {
				m_CreatePentagon = true;
			}
			decideShape = m_pShape[i];
			goto deside;
		}
	}
	deside:
		if(m_CreatePentagon == true){
		decideShape->setPlan(true);
	}
		else {
			decideShape->setPlan(false);
		}

	// ˄
}

Field::~Field()
{
	// ˅

	// ˄
}

// ˅

// ˄
