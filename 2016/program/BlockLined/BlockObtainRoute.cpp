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

	m_ViaPlaceNumber = (m_ViaPlaceNumber>10)?10:m_ViaPlaceNumber;//�z��11�����Ȃ��̂�MAX11�ɂ���

	if (m_ViaPlaceNumber >= 0) {								//1��ڂ̓X�^�[�g�u����
		m_pViaPoint[0] = m_pStartPoint->getNextPlace(0);//�z���0�Ԃɓ����
	}

	for(int i=0; i<m_ViaPlaceNumber;i++){						//2��ڈȍ~�͓r���u����@�ړ��ʕ��J��Ԃ�
		m_pViaPoint[i+1] = m_pViaPoint[i]->getNextPlace(i+1);//�z��i+�ɓ����
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
