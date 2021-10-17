//S)
#include "Place.h"

#include "BlockLined/Block.h"
#include "BlockLined/RouteInfo.h"

//E)

Place::Place(Block* pBlock, int xcoord, RouteInfo* pRouteInfo, Block* pBlockA, Block* pBlockB, Block* pBlockC, Block* pBlockD)
//S)
:m_Distance(100),m_XCoordinate(xcoord),m_YCoordinate(0),m_pArrangementBlock(pBlock),m_pRouteInfo(pRouteInfo)
//E)
{
	//S)
	for(int i =0; i<4; i++){
		m_pAdjoinPlace[i] = nullptr;
	}

	m_pBlock[0]=pBlockA;
	m_pBlock[1]=pBlockB;
	m_pBlock[2]=pBlockC;
	m_pBlock[3]=pBlockD;
	//E)
}

int Place::getDistance()
{
	//S)
	return m_Distance;
	//E)
}

void Place::setDistance(int distance)
{
	//S)
	if( m_Distance > distance){
		m_Distance = distance;
	}
	//E)
}

void Place::setDistanceInit(int distance)
{
	//S)
	m_Distance = distance;
	//E)
}

void Place::ResetDistance()
{
	//S)
	m_Distance = 100;
	//E)
}

void Place::addAdjoinPlace(Place* pFrontPlace, Place* pRightPlace, Place* pLeftPlace, Place* pBackPlace)
{
	//S)
	m_pAdjoinPlace[0] = pFrontPlace;
	m_pAdjoinPlace[1] = pRightPlace;
	m_pAdjoinPlace[2] = pLeftPlace;
	m_pAdjoinPlace[3] = pBackPlace;
	//E)
}

void Place::setAdjoinDistance()
{
	//S)
	//�אڂ���4�̒u����ɁA���̂������
	for (int i = 0; i < 4 ; i++) {
		if(m_pAdjoinPlace[i] != nullptr){						//�u���ꂪ�L��
			if(m_pAdjoinPlace[i]->getDistance() >m_Distance+1){	//����̓��̂肪�����{�P���傫�����
				m_pAdjoinPlace[i]->setDistance(m_Distance+1);	//�����̓��̂�{�P������
			}
		}
	}
	//E)
}

Place* Place::getNextPlace(int list_num)
{
	//S)
	int direction = m_pRouteInfo->getRunDirection();
	int x = 1;
	int y = 1;
	int z = 1;
	int w = 1;

	switch (direction)
	{
	case 1:
		x = 1; y = 2; z = 3; w = 4;
		break;

	case 2:
		x = 2; y = 4; z = 1; w = 3;
		break;

	case 3:
		x = 3; y = 1; z = 4; w = 2;
		break;

	//default:
	case 4:
		x = 4; y = 3; z = 2; w = 1;
		break;
	}

	bool flag = false;
	int num = 0;

	if (flag == false && m_pAdjoinPlace[x - 1] != nullptr) {
		if (getBlockExistence() == true) {
			if (m_Distance - 1 == m_pAdjoinPlace[x - 1]->getDistance()) {
				m_pRouteInfo->setProcess(list_num, 1105);//�T�̓u���b�N�𒴂��đO�ɐi��
				m_pRouteInfo->setRunDirection(x);
				flag = true;
				num = x - 1;
			}
		}
		else {
			if (m_Distance - 1 == m_pAdjoinPlace[x - 1]->getDistance()) {
				m_pRouteInfo->setProcess(list_num, 1001);//�P�͑O�ɐi��
				m_pRouteInfo->setRunDirection(x);
				flag = true;
				num = x - 1;
			}
		}
	}
	

	if (flag == false && m_pAdjoinPlace[y - 1] != nullptr) {
		if (getBlockExistence() == true) {
			if (m_Distance - 1 == m_pAdjoinPlace[y - 1]->getDistance()) {
				m_pRouteInfo->setProcess(list_num, 111206);//�U�̓u���b�N�𒴂��ĉE�ɐi��
				m_pRouteInfo->setRunDirection(y);
				flag = true;
				num = y - 1;
			}
		}
		else {
			if (m_Distance - 1 == m_pAdjoinPlace[y - 1]->getDistance()) {
				m_pRouteInfo->setProcess(list_num, 1002);//�Q�͉E�ɐi��
				m_pRouteInfo->setRunDirection(y);
				flag = true;
				num = y - 1;
			}
		}
	}

	if (flag == false && m_pAdjoinPlace[z - 1] != nullptr) {
		if (getBlockExistence() == true) {
			if (m_Distance - 1 == m_pAdjoinPlace[z - 1]->getDistance()) {
				m_pRouteInfo->setProcess(list_num, 111207);//�V�͍��Ƀu���b�N�𒴂��Đi��
				m_pRouteInfo->setRunDirection(z);
				flag = true;
				num = z - 1;
			}
		}
		else {
			if (m_Distance - 1 == m_pAdjoinPlace[z - 1]->getDistance()) {
				m_pRouteInfo->setProcess(list_num, 1003);//�R�͍��ɐi��
				m_pRouteInfo->setRunDirection(z);
				flag = true;
				num = z - 1;
			}
		}
	}

	if (flag == false && m_pAdjoinPlace[w - 1] != nullptr) {
		if (getBlockExistence() == true) {
			if (m_Distance - 1 == m_pAdjoinPlace[w - 1]->getDistance()) {
				m_pRouteInfo->setProcess(list_num, 1108);//�W�͂��̂܂܌���
				m_pRouteInfo->setRunDirection(w);
				flag = true;
				num = w - 1;
			}
		}

		else {
			if (m_Distance - 1 == m_pAdjoinPlace[w - 1]->getDistance()) {
				m_pRouteInfo->setProcess(list_num, 1004);//�S�̓u���b�N�������Č���
				m_pRouteInfo->setRunDirection(w);
				flag = true;
				num = w - 1;
			}
		}
	}

	if (flag == false) {
			m_pRouteInfo->setProcess(list_num, 1108);//�W�͂��̂܂܌���
			m_pRouteInfo->setRunDirection(w);
			flag = true;
			num = w - 1;
	}

	return m_pAdjoinPlace[num];
	//E)
}

int Place::getBackPlace(int bodyDirection)
{
	//S)
	int back = 1;
	switch(bodyDirection){
	case 1:
		back = 4;
		break;
	case 2:
		back = 3;
		break;
	case 3:
		back = 2;
		break;
	case 4:
		back = 1;
		break;
	}
	int placenum = m_pAdjoinPlace[back-1]->getXcoord();
	return placenum;
	//E)
}

bool Place::getArrangeBlockExistence()
{
	//S)
	//�z�u�σu���b�N�����鎞��true
	if(m_pArrangementBlock != nullptr){
		return m_pArrangementBlock->getArrangement();
	}
	else{
		return false;
	}
	//E)
}

bool Place::getBlockExistence()
{
	//S)
	//�z�u�u���b�N(������u���b�N)�����鎞��true
		if(m_pArrangementBlock != nullptr){
		return true;
	}
		else {
			return false;
		}
	//E)
}

int Place::getBlock()
{
	//S)
	return m_pArrangementBlock->getBlockNumber();
	//E)
}

Place::~Place()
{
	//S)
	
	//E)
}

int Place::getXcoord()
{
	//S)
	return m_XCoordinate;
	//E)
}

void Place::setBlock(int blockNum)
{
	//S)
	if(blockNum == 5){
		m_pArrangementBlock = nullptr;
	}
	else{
		m_pArrangementBlock = m_pBlock[blockNum];
	}

	//E)
}

//S)

//E)
