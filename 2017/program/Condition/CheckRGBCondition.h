//S)

//E)

#ifndef CONDITION_CHECKRGBCONDITION_H
#define CONDITION_CHECKRGBCONDITION_H

//S)
#include "Condition/Condition.h"
#include "ColorSensor.h"

using namespace ev3api;
//E)

class CheckRGBCondition : public Condition
{
	//S)
	
	//E)

private:

	ColorSensor* m_pColorSensor;

	bool m_TF;

public:

	CheckRGBCondition(ColorSensor* pColorSensor, bool TF);

	bool isSatisfy();

	~CheckRGBCondition();

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
