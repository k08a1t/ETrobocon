//S)

//E)

#ifndef CONDITION_HSLCONDITION_H
#define CONDITION_HSLCONDITION_H

//S)
#include "Condition/Condition.h"
#include "ColorSensor.h"

using namespace ev3api;
//E)

class HSLCondition : public Condition
{
	//S)
	
	//E)

private:

	ColorSensor* m_pColorSensor;

	bool m_TF;

	bool m_Result_TF;

public:

	HSLCondition(ColorSensor* pColorSensor, bool TF);

	bool isSatisfy();

	~HSLCondition();

	//S)
	int m_log[3];
	void log(int &loga, int &logb, int &logc);
	//E)
};

//S)

//E)

#endif	// CONDITION_HSLCONDITION_H

//S)

//E)
