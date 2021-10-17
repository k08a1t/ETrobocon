//S)

//E)

#ifndef BLOCKLINED_ESCAPEROUTE_H
#define BLOCKLINED_ESCAPEROUTE_H

//S)
#include "BlockLined/Route.h"
#include "BlockLined/Field.h"
#include "BlockLined/Block.h"
#include "BlockLined/Place.h"
#include "BlockLined/RouteInfo.h"
//E)

class EscapeRoute : public Route
{
	//S)
	
	//E)

public:

	EscapeRoute(Field* pFilde, RouteInfo* pRouteInfo);

	int SearchRoute();

	~EscapeRoute();

	//S)
	
	//E)
};

//S)

//E)

#endif	// BLOCKLINED_ESCAPEROUTE_H

//S)

//E)
