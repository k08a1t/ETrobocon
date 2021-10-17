//S)

//E)

#ifndef BLOCKLINED_ROUTE_H
#define BLOCKLINED_ROUTE_H

//S)
#include "BlockLined/Field.h"
#include "BlockLined/Block.h"
#include "BlockLined/Place.h"
#include "BlockLined/RouteInfo.h"


//E)

class Route
{
	//S)
	
	//E)

private:

	int m_ViaPlaceNumber;

	int m_Place_listnum;

protected:

	Place* m_pViaPoint[12];

	Place* m_pGoalPoint;

	Place* m_pStartPoint;

	Field* m_pField;

	RouteInfo* m_pRouteInfo;

	Place* m_pPlace[16];

private:

	Block* m_pTransportBlock[4];

public:

	Route(Field* pFilde, RouteInfo* pRouteInfo, Block* pBlockA, Block* pBlockB, Block* pBlockC, Block* pBlockD);

	int obtainSearchRoute();

	int tranportSearchRoute();

	int escapeSearchRoute();

	int getRunbodyDirection();

	int getTransportBlock();

	int getTravelDirection(int num);

	void SettingBlockRoute();

	void addPlace(Place* pPlace);

	virtual ~Route();

	//S)
	int m_log[3];
	void log(int &loga, int &logb, int &logc);
	//E)
};

//S)

//E)

#endif	// BLOCKLINED_ROUTE_H

//S)

//E)
