//S)

//E)

#ifndef BLOCKLINED_BLOCKTRANSPORTROUTE_H
#define BLOCKLINED_BLOCKTRANSPORTROUTE_H

//S)
#include "BlockLined/Route.h"
#include "BlockLined/Field.h"
#include "BlockLined/Block.h"
#include "BlockLined/Place.h"
#include "BlockLined/RouteInfo.h"
//E)

class BlockTransportRoute : public Route
{
	//S)
	
	//E)

public:

	BlockTransportRoute(Field* pFilde, RouteInfo* pRouteInfo);

	int SearchRoute();

	~BlockTransportRoute();

	//S)
	
	//E)
};

//S)

//E)

#endif	// BLOCKLINED_BLOCKTRANSPORTROUTE_H

//S)

//E)
