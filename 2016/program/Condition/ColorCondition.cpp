//S)
#include "ColorCondition.h"
#include "ColorSensor.h"

using namespace ev3api;
//E)
 
ColorCondition::ColorCondition(int t_color, ColorSensor* pColorSensor)
//S)
	: m_target_color(t_color)
//E)
{
	//S)
	m_pColorSensor = pColorSensor;
	//E)
}

bool ColorCondition::isSatisfy()
{
	//S)
	switch (m_target_color){
	case 0:
		if(0==m_pColorSensor->getColorNumber()){
			return false;
		}
		else {
			return true;
		}
		break;
	case 1:
		if (1 == m_pColorSensor->getColorNumber()) {
			return false;
		}
		else {
			return true;
		}
		break;
	case 2:
		if (2 == m_pColorSensor->getColorNumber()) {
			return true;
		}
		else {
			return false;
		}
		break;
	case 3:
		if (3 == m_pColorSensor->getColorNumber()) {
			return true;
		}
		else {
			return false;
		}
		break;
	case 4:
		if (4 == m_pColorSensor->getColorNumber()||6 == m_pColorSensor->getColorNumber()) {
			return true;
		}
		else {
			return false;
		}
		break;
	case 5:
		if(5==m_pColorSensor->getColorNumber()){
			return true;
		}
		else {
			return false;
		}
		break;
	default:
		if (0 != m_pColorSensor->getColorNumber() && 1 != m_pColorSensor->getColorNumber()&& 2 != m_pColorSensor->getColorNumber() && 6 != m_pColorSensor->getColorNumber()&&7 != m_pColorSensor->getColorNumber()) {
			return true;
		}
		else {
			return false;
		}
		break;
	}
	//E)
}

ColorCondition::~ColorCondition()
{
	//S)
	
	//E)
}

//S)

//E)
