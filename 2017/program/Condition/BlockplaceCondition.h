//S)

//E)

#ifndef CONDITION_BLOCKPLACECONDITION_H
#define CONDITION_BLOCKPLACECONDITION_H

//S)
#include "Condition/Condition.h"
#include "ColorSensor.h"

using namespace ev3api;
//E)

class BlockplaceCondition : public Condition
{
	//S)
	
	//E)

private:

	ColorSensor* m_pColorSensor;

public:

	BlockplaceCondition(ColorSensor* pColorSensor);

	bool isSatisfy();

	~BlockplaceCondition();

	//S)
	int m_log[3];
	void log(int &loga, int &logb, int &logc);
	//E)
};

//S)

//E)

#endif	// CONDITION_BLOCKPLACECONDITION_H

//S)

//E)
