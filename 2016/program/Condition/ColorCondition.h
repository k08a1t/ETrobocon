//S)

//E)

#ifndef CONDITION_COLORCONDITION_H
#define CONDITION_COLORCONDITION_H

//S)
#include "Condition/Condition.h"
#include "ColorSensor.h"

using namespace ev3api;
//E)

class ColorCondition : public Condition
{
	//S)
	
	//E)

private:

	int m_target_color;

	ColorSensor* m_pColorSensor;

public:

	ColorCondition(int t_color, ColorSensor* pColorSensor);

	bool isSatisfy();

	~ColorCondition();

	//S)
	
	//E)
};

//S)

//E)

#endif	// CONDITION_COLORCONDITION_H

//S)

//E)
