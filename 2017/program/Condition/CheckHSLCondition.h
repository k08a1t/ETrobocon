//S)

//E)

#ifndef CONDITION_CHECKHSLCONDITION_H
#define CONDITION_CHECKHSLCONDITION_H

//S)
#include "Condition/Condition.h"
#include "ColorSensor.h"

using namespace ev3api;
//E)

class CheckHSLCondition : public Condition
{
	//S)
	
	//E)

private:

	ColorSensor* m_pColorSensor;

	bool m_TF;

public:

	CheckHSLCondition(ColorSensor* pColorSensor, bool TF);

	bool isSatisfy();

	~CheckHSLCondition();

	//S)
	int m_log[3];
	void log(int &loga, int &logb, int &logc);
	//E)
};

//S)

//E)

#endif	// CONDITION_CHECKHSLCONDITION_H

//S)

//E)
