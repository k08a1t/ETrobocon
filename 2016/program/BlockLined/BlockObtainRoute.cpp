//S)
#include "BlockObtainRoute.h"
#include "BlockLined/Route.h"
#include "BlockLined/Block.h"
#include "BlockLined/Field.h"
#include "BlockLined/Place.h"
#include "BlockLined/RouteInfo.h"


//E)

int BlockObtainRoute::SearchRoute()
{
	//S)
	
//m_log[0]=m_pField->getPresentPoint();


	m_pStartPoint = m_pField->getPresentPoint();

	m_pGoalPoint = m_pField->JudgementClosestBlock();

	Block* pTransportBlock = m_pGoalPoint->getBlock();
	m_pRouteInfo->setBlock(pTransportBlock);

	m_ViaPlaceNumber = m_pGoalPoint->getDistance() - 1;//

	m_pField->MakeDistanceList(m_pGoalPoint, false);

	m_ViaPlaceNumber = (m_ViaPlaceNumber>10)?10:m_ViaPlaceNumber;//配列が11しかないのでMAX11にする

	if (m_ViaPlaceNumber >= 0) {								//1回目はスタート置き場
		m_pViaPoint[0] = m_pStartPoint->getNextPlace(0);//配列の0番に入れる
	}

	for(int i=0; i<m_ViaPlaceNumber;i++){						//2回目以降は途中置き場　移動量分繰り返す
		m_pViaPoint[i+1] = m_pViaPoint[i]->getNextPlace(i+1);//配列i+に入れる
	}

	int num = m_pGoalPoint->getXcoord();
	m_pField->DecisionPresentPoint(num);

	return m_ViaPlaceNumber + 1;
	//E)
}

BlockObtainRoute::BlockObtainRoute(Field* pFilde, RouteInfo* pRouteInfo)
//S)
:Route(pFilde,pRouteInfo)
//E)
{
	//S)

	//E)
}

BlockObtainRoute::~BlockObtainRoute()
{
	//S)
	
	//E)
}

//S)

//E)
