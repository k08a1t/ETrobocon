//S)

//E)

#ifndef BLOCKLINED_ROUTEINFO_H
#define BLOCKLINED_ROUTEINFO_H

//S)
#include "BlockLined/Block.h"
//E)

class RouteInfo
{
	//S)
	
	//E)

private:

	int m_RunbodyDirection;

	int m_Process[20];

	int m_blockNumber;

	Block* m_pTransportBlock;

public:

	RouteInfo(int rundirection);

	void setRunDirection(int direction);

	void setProcess(int num, int acceed);

	int getRunDirection();

	int getProcess(int num);

	void setBlock(int BlockNum);

	int getBlock();

	~RouteInfo();

	//S)
	int m_log[6];
	void log(int &loga, int &logb, int &logc, int &logd, int &loge, int &logf);
	//E)
};

//S)

//E)

#endif	// BLOCKLINED_ROUTEINFO_H

//S)

//E)
