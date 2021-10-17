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

	m_pStartPoint->setBlock(5);//ルートの開始する置き場にあるブロックをなくす。５はnullptrを代入することになる

	m_ViaPlaceNumber = (m_ViaPlaceNumber>10)?10:m_ViaPlaceNumber;//配列が11しかないのでMAX11にする

	if (m_ViaPlaceNumber >= 0) {								//1回目はスタート置き場
		m_pViaPoint[0] = m_pStartPoint->getNextPlace(0);//配列の0番に入れる
	}

	for(int i=0; i<m_ViaPlaceNumber;i++){						//2回目以降は途中置き場　移動量分繰り返す
		m_pViaPoint[i+1] = m_pViaPoint[i]->getNextPlace(i+1);//配列i+に入れる
	}

	m_pGoalPoint->setBlock(TransportBlock);//開始の置き場からなくしたブロックを配置する。５はnullptrを代入することになる
	
	int num = m_pGoalPoint->getXcoord();//現在地を更新する
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

	m_ViaPlaceNumber = (m_ViaPlaceNumber>10)?10:m_ViaPlaceNumber;//配列が11しかないのでMAX11にする

	if (m_ViaPlaceNumber >= -1) {								//1回目はスタート置き場
		m_pViaPoint[0] = m_pStartPoint->getNextPlace(0);//配列の0番に入れる
	}

	for(int i = 0; i < m_ViaPlaceNumber;i++){						//2回目以降は途中置き場　移動量分繰り返す
		m_pViaPoint[i+1] = m_pViaPoint[i]->getNextPlace(i+1);//配列i+に入れる
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
