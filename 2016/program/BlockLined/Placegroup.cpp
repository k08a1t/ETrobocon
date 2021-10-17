//S)
#include "Placegroup.h"

#include "BlockLined/Place.h"

using namespace ev3api;
//E)

Placegroup::Placegroup(Place* pPlace1, Place* pPlace2, Place* pPlace3, Place* pPlace4)
//S)

//E)
{
	//S)
	m_pPlace[0] = pPlace1;
	m_pPlace[1] = pPlace2;
	m_pPlace[2] = pPlace3;
	m_pPlace[3] = pPlace4;
	//E)
}

int Placegroup::getNearestPlace()
{
	//S)
	int ReturnNumber = 0;
	int judgment = 100;
	for(int i=0; i<4; i++){
		if(m_pPlace[i]->getDistance() < judgment && m_pPlace[i]->getDistance() > -1){
			judgment = m_pPlace[i]->getDistance();
			ReturnNumber = i;
		}
	}

	return m_pPlace[ReturnNumber]->getXcoord();
	//E)
}

Placegroup::~Placegroup()
{
	//S)
	
	//E)
}

//S)

//E)
