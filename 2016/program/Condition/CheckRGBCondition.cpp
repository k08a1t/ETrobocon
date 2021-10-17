//S)
#include "CheckRGBCondition.h"
#include "ColorSensor.h"

using namespace ev3api;
//E)

CheckRGBCondition::CheckRGBCondition(ColorSensor* pColorSensor, bool TF)
//S)
	: m_TF(TF)
//E)
{
	//S)
	m_pColorSensor = pColorSensor;
	//E)
}

bool CheckRGBCondition::isSatisfy()
{
	//S)
	rgb_raw_t rgb_val;
	m_pColorSensor->getRawColor(rgb_val);
	int r = rgb_val.r;
	int g = rgb_val.g;
	int b = rgb_val.b;

	if (m_TF == true) {
		r = (r > 250) ? 250 : r;

		r = (r > 170) ? 250 : r;
		r = (r < 50) ? 50 : r;//r = (r < 35) ? 50 : r;

		g = (g > 250) ? 250 : g;

		g = (g > 60) ? 250 : g;
		g = (g < 50) ? 50 : g;

		b = (b > 250) ? 250 : b;

		b = (b > 70) ? 250 : b;
		b = (b < 45) ? 50 : b;

		m_log[0] = r;
		m_log[1] = g;
		m_log[2] = b;
	}
	else {
		m_log[0] = r;
		m_log[1] = g;
		m_log[2] = b;
	}

	


				//////Ô///‰©///Â///—Î
	int rbase[4] = { 250, 250,  50,  50 };
	int gbase[4] = {  50, 250, 250, 250 };
	int bbase[4] = {  50,  50, 250,  50 };


	if (r == rbase[0] && g == gbase[0] && b == bbase[0]) {
		return false;//red
	}
	else if (r == rbase[1] && g == gbase[1] && b == bbase[1]) {
		return false;//yellow
	}
	else if (r == rbase[2] && g == gbase[2] && b == bbase[2]) {
		return false;//blue
	}
	else if (r == rbase[3] && g == gbase[3] && b == bbase[3]) {
		return false;//green
	}
	else {
		return false;
	}
	//E)
}

CheckRGBCondition::~CheckRGBCondition()
{
	//S)
	
	//E)
}

//S)
void CheckRGBCondition::log(int &loga, int &logb,int &logc)
{
	loga = m_log[0];
	logb = m_log[1];
	logc = m_log[2];
}
//E)
