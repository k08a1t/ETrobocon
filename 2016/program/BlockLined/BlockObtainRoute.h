//S)

//E)

#ifndef BLOCKLINED_BLOCKOBTAINROUTE_H
#define BLOCKLINED_BLOCKOBTAINROUTE_H

//S)
#include "BlockLined/Route.h"
#include "BlockLined/Field.h"
#include "BlockLined/Block.h"
#include "BlockLined/Place.h"
#include "BlockLined/RouteInfo.h"
//E)

class BlockObtainRoute : public Route
{
	//S)
	
	//E)

public:

	int SearchRoute();

	BlockObtainRoute(Field* pFilde, RouteInfo* pRouteInfo);

	~BlockObtainRoute();

	//S)
	
	//E)
};

//S)

//E)

#endif	// BLOCKLINED_BLOCKOBTAINROUTE_H

//S)

//E)
