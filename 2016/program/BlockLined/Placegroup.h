//S)

//E)

#ifndef BLOCKLINED_PLACEGROUP_H
#define BLOCKLINED_PLACEGROUP_H

//S)
#include "BlockLined/Color.h"
#include "BlockLined/Place.h"
//E)

class Placegroup
{
	//S)
	
	//E)

private:

	Color m_Color;

	Place* m_pPlace[4];

public:

	Placegroup(Place* pPlace1, Place* pPlace2, Place* pPlace3, Place* pPlace4);

	int getNearestPlace();

	~Placegroup();

	//S)
	
	//E)
};

//S)

//E)

#endif	// BLOCKLINED_PLACEGROUP_H

//S)

//E)
