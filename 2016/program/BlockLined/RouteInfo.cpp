//S)
#include "RouteInfo.h"

#include "BlockLined/Block.h"
//E)

RouteInfo::RouteInfo(int rundirection)
//S)
  : m_RunbodyDirection(rundirection),m_blockNumber(1)
//E)
{
	//S)
	m_Process[0] = 1003;
	m_Process[1] = 1001;
	m_Process[2] = 111206;
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
	//E)
}

void RouteInfo::setRunDirection(int direction)
{
	//S)
	m_RunbodyDirection = direction;
	//E)
}

void RouteInfo::setProcess(int num, int acceed)
{
	//S)
	m_Process[num] = acceed;
	//E)
}

int RouteInfo::getRunDirection()
{
	//S)
	return m_RunbodyDirection;
	//E)
}

int RouteInfo::getProcess(int num)
{
	//S)
	return m_Process[num];
	//E)
}

void RouteInfo::setBlock(int BlockNum)
{
	//S)
	m_blockNumber = BlockNum;
	//E)
}

int RouteInfo::getBlock()
{
	//S)
	return m_blockNumber;
	//E)
}

RouteInfo::~RouteInfo()
{
	//S)
	
	//E)
}

//S)
void RouteInfo::log(int &loga, int &logb, int &logc, int &logd, int &loge, int &logf)
{
	loga = m_Process[0];
	logb = m_Process[1];
	logc = m_Process[2];
	logd = m_Process[3];
	loge = m_Process[4];
	logf = m_Process[5];
}
//E)
