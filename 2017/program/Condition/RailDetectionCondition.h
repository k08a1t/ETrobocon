//S)

//E)

#ifndef CONDITION_RAILDETECTIONCONDITION_H
#define CONDITION_RAILDETECTIONCONDITION_H

//S)
#include "Condition/Condition.h"
#include "ColorSensor.h"

using namespace ev3api;
//E)

class RailDetectionCondition : public Condition
{
	//S)
	
	//E)

private:

	ColorSensor* m_pColorSensor;

	bool m_TF;

	bool m_Result_TF;

public:

	RailDetectionCondition(ColorSensor* pColorSensor, bool TF);

	bool isSatisfy();

	~RailDetectionCondition();

	//S)
	int m_log[3];
	void log(int &loga, int &logb, int &logc);
	//E)
};

//S)

//E)

#endif	// CONDITION_RAILDETECTIONCONDITION_H

//S)

//E)
