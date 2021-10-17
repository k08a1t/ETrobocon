//S)

//E)

#ifndef BLOCKLINED_FIELD_H
#define BLOCKLINED_FIELD_H

//S)
#include "BlockLined/Place.h"
#include "BlockLined/Placegroup.h"
//E)

class Field
{
	//S)
	
	//E)

private:

	Place* m_PresentPoint;

	int m_Place_listnum;

	int m_Placegroup_listnum;

	Placegroup* m_pPlacegroup[5];

	Place* m_pPlace[16];

public:

	Field(Place* pPresentPlace);

	void MakeDistanceList(int StartPointNum, bool blockade);

	int JudgementArrangementPoint(Color color);

	int JudgementClosestBlock();

	void DecisionPresentPoint(int NewPresentPoint);

	void addPlace(Place* pPlace);

	void addPlacegroup(Placegroup* pPlacegroup);

	Place* getPresentPoint();

	~Field();

	//S)
	int m_log[16];
	void log(int &loga, int &logb, int &logc, int &logd, int &loge, int &logf, int &logg, int &logh, int &logi, int &logj, int &logk, int &logl, int &logm, int &logn, int &logo, int &logp);
	//E)
};

//S)

//E)

#endif	// BLOCKLINED_FIELD_H

//S)

//E)
