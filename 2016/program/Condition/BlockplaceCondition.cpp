//S)
#include "BlockplaceCondition.h"
#include "ColorSensor.h"

using namespace ev3api;
//E)

BlockplaceCondition::BlockplaceCondition(ColorSensor* pColorSensor)
//S)
	
//E)
{
	//S)
	m_pColorSensor = pColorSensor;
	//E)
}

bool BlockplaceCondition::isSatisfy()
{
	//S)
	rgb_raw_t rgb_val;
	m_pColorSensor->getRawColor(rgb_val);
	int r = rgb_val.r;
	int g = rgb_val.g;
	int b = rgb_val.b;

	r = (r > 250) ? 250 : r;

	r = (r > 158) ? 250 : r;//170
	r = (r < 50) ? 50 : r;

	g = (g > 250) ? 250 : g;

	g = (g > 60) ? 250 : g;
	g = (g < 50) ? 50 : g;

	b = (b > 250) ? 250 : b;

	b = (b > 63) ? 250 : b;
	b = (b < 45) ? 50 : b;


	m_log[0] = r;
	m_log[1] = g;
	m_log[2] = b;


				//////Ô///‰©///Â///—Î
	int rbase[4] = { 250, 250,  50,  50 };
	int gbase[4] = {  50, 250, 250, 250 };
	int bbase[4] = {  50,  50, 250,  50 };


	if (r == rbase[0] && g == gbase[0] && b == bbase[0]) {
		return true;//red
	}
	else if (r == rbase[1] && g == gbase[1] && b == bbase[1]) {
		return true;//yellow
	}
	else if (r == rbase[2] && g == gbase[2] && b == bbase[2]) {
		return true;//blue
	}
	else if (r == rbase[3] && g == gbase[3] && b == bbase[3]) {
		return true;//green
	}
	else {
		return false;
	}
	//E)
}

BlockplaceCondition::~BlockplaceCondition()
{
	//S)
	
	//E)
}

//S)
void BlockplaceCondition::log(int &loga, int &logb,int &logc)
{
	loga = m_log[0];
	logb = m_log[1];
	logc = m_log[2];
}
//E)
