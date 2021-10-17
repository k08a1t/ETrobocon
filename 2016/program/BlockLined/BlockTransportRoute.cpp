//S)
#include "BlockTransportRoute.h"

#include "BlockLined/Route.h"
#include "BlockLined/Block.h"
#include "BlockLined/Field.h"
#include "BlockLined/Place.h"
#include "BlockLined/Color.h"
#include "BlockLined/RouteInfo.h"

//E)

BlockTransportRoute::BlockTransportRoute(Field* pFilde, RouteInfo* pRouteInfo)
//S)
:Route(pFilde,pRouteInfo)
//E)
{
	//S)
	
	//E)
}

int BlockTransportRoute::SearchRoute()
{
	//S)
	//m_pStartPoint = m_pField->getPresentPoint();

	//Color blockColor = m_pTransportBlock->ObtainmentColor();
	//m_pGoalPoint = m_pField->JudgementArrangementPoint(blockColor);

	//m_ViaPlaceNumber = m_pGoalPoint->getDistance() - 1;

	//m_pField->MakeDistanceList(m_pGoalPoint, false);

	//int RunBodyDirection = m_RunbodyDirection;
	//int acceedDirection = 0;

	//m_ViaPlaceNumber=(m_ViaPlaceNumber>10)?10:m_ViaPlaceNumber;//配列が11しかないのでMAX11にする

	//if (m_ViaPlaceNumber >= 0) {								//1回目はスタート置き場
	//	m_pViaPoint[0] = m_pStartPoint->getNextPlace(RunBodyDirection,acceedDirection);
	///	m_Process[0] = acceedDirection;
	//}
	//for(int i=0; i<m_ViaPlaceNumber;i++){						//2回目以降は途中置き場　移動量分繰り返す
	//	m_pViaPoint[i+1] = m_pViaPoint[i]->getNextPlace(RunBodyDirection,acceedDirection);
	//	m_Process[i+1] = acceedDirection;
	//}
	//m_RunbodyDirection = RunBodyDirection;
	//m_pField->DecisionPresentPoint(m_pGoalPoint);

	return 2;//m_ViaPlaceNumber + 1;
	//E)
}

BlockTransportRoute::~BlockTransportRoute()
{
	//S)
	
	//E)
}

//S)

//E)
