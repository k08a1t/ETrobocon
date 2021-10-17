//S)
#include "Route.h"

#include "BlockLined/Place.h"
#include "BlockLined/Field.h"
#include "BlockLined/Block.h"
#include "BlockLined/RouteInfo.h"
#include "BlockLined/Color.h"

//E)

Route::Route(Field* pFilde, RouteInfo* pRouteInfo, Block* pBlockA, Block* pBlockB, Block* pBlockC, Block* pBlockD)
  : m_ViaPlaceNumber(0)
  , m_Place_listnum(0)
//S)
,m_pGoalPoint(nullptr),m_pField(pFilde),m_pRouteInfo(pRouteInfo)
//E)
{
	//S)
	m_pTransportBlock[0]=pBlockA;
	m_pTransportBlock[1]=pBlockB;
	m_pTransportBlock[2]=pBlockC;
	m_pTransportBlock[3]=pBlockD;
	m_log[0] = 0;
	m_log[1] = 0;
	m_log[2] = 0;
	//E)
}

int Route::obtainSearchRoute()
{
	//S)
	
	m_pStartPoint = m_pField->getPresentPoint();

	int GoalPlaceNum = m_pField->JudgementClosestBlock();

	m_pGoalPoint = m_pPlace[GoalPlaceNum];
	int TransportBlock = m_pGoalPoint->getBlock();
	m_pRouteInfo->setBlock(TransportBlock);

	m_ViaPlaceNumber = m_pGoalPoint->getDistance() -1;//

	m_pField->MakeDistanceList(GoalPlaceNum, true);//false

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

int Route::tranportSearchRoute()
{
	//S)
	m_pStartPoint = m_pField->getPresentPoint();

	int TransportBlock = m_pRouteInfo->getBlock();
	Color blockColor = m_pTransportBlock[TransportBlock]->ObtainmentColor();

	int GoalPlaceNum2 = m_pField->JudgementArrangementPoint(blockColor);
	m_pGoalPoint = m_pPlace[GoalPlaceNum2];

	m_ViaPlaceNumber = m_pGoalPoint->getDistance() - 1;

	m_pField->MakeDistanceList(GoalPlaceNum2, false);

	m_pStartPoint->setBlock(5);//���[�g�̊J�n����u����ɂ���u���b�N���Ȃ����B�T��nullptr�������邱�ƂɂȂ�

	m_ViaPlaceNumber = (m_ViaPlaceNumber>10)?10:m_ViaPlaceNumber;//�z��11�����Ȃ��̂�MAX11�ɂ���

	if (m_ViaPlaceNumber >= 0) {								//1��ڂ̓X�^�[�g�u����
		m_pViaPoint[0] = m_pStartPoint->getNextPlace(0);//�z���0�Ԃɓ����
	}

	for(int i=0; i<m_ViaPlaceNumber;i++){						//2��ڈȍ~�͓r���u����@�ړ��ʕ��J��Ԃ�
		m_pViaPoint[i+1] = m_pViaPoint[i]->getNextPlace(i+1);//�z��i+�ɓ����
	}

	m_pGoalPoint->setBlock(TransportBlock);//�J�n�̒u���ꂩ��Ȃ������u���b�N��z�u����B�T��nullptr�������邱�ƂɂȂ�
	
	int num = m_pGoalPoint->getXcoord();//���ݒn���X�V����
	m_pField->DecisionPresentPoint(num);

	return m_ViaPlaceNumber + 1;
	//E)
}

int Route::escapeSearchRoute()
{
	//S)
		m_pStartPoint = m_pField->getPresentPoint();

	int GoalPlaceNum3 = m_pField->JudgementArrangementPoint(Black);
	m_pGoalPoint = m_pPlace[GoalPlaceNum3];

	m_ViaPlaceNumber = m_pGoalPoint->getDistance() - 1;

	m_pField->MakeDistanceList(GoalPlaceNum3, true);

	m_ViaPlaceNumber = (m_ViaPlaceNumber>10)?10:m_ViaPlaceNumber;//�z��11�����Ȃ��̂�MAX11�ɂ���

	if (m_ViaPlaceNumber >= -1) {								//1��ڂ̓X�^�[�g�u����
		m_pViaPoint[0] = m_pStartPoint->getNextPlace(0);//�z���0�Ԃɓ����
	}

	for(int i = 0; i < m_ViaPlaceNumber;i++){						//2��ڈȍ~�͓r���u����@�ړ��ʕ��J��Ԃ�
		m_pViaPoint[i+1] = m_pViaPoint[i]->getNextPlace(i+1);//�z��i+�ɓ����
	}

	int num = m_pGoalPoint->getXcoord();
	m_pField->DecisionPresentPoint(num);

	return m_ViaPlaceNumber + 1;
	//E)
}

int Route::getRunbodyDirection()
{
	//S)
	return m_pRouteInfo->getRunDirection();
	//E)
}

int Route::getTransportBlock()
{
	//S)
	return m_pRouteInfo->getBlock();
	//E)
}

int Route::getTravelDirection(int num)
{
	//S)
	return m_pRouteInfo->getProcess(num);
	//E)
}

void Route::SettingBlockRoute()
{
	//S)
	int direct = m_pRouteInfo->getRunDirection();
	Place* pNowPoint =m_pField->getPresentPoint();
	int placenum = pNowPoint->getBackPlace(direct);
	m_pField->DecisionPresentPoint(placenum);

	switch (direct) {
	case 1:
		direct = 4;
		break;
	case 2:
		direct = 3;
		break;
	case 3:
		direct = 2;
		break;
	case 4:
		direct = 1;
		break;
	}

	m_pRouteInfo->setRunDirection(direct);
	//E)
}

void Route::addPlace(Place* pPlace)
{
	//S)
	m_pPlace[m_Place_listnum] = pPlace;
	m_Place_listnum++;
	//E)
}

Route::~Route()
{
	//S)
	
	//E)
}

//S)
void Route::log(int &loga, int &logb,int &logc)
{
	loga = m_log[0];
	logb = m_log[1];
	logc = m_log[2];
}
//E)
