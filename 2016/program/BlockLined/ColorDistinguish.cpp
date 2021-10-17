//S)
#include "ColorDistinguish.h"

#include "ColorSensor.h"
#include "BlockLined/Color.h"

using namespace ev3api;
//E)

ColorDistinguish::ColorDistinguish(ColorSensor* pColorSensor)
//S)
:m_UnecidedDegree(1000),m_pColorSensor(pColorSensor)
//E)
{
	//S)
	
	//E)
}

Color ColorDistinguish::BlockcolorDistinguish()
{
	//S)
    rgb_raw_t rgb_val;
	m_pColorSensor->getRawColor(rgb_val);
	int rbase[5] = { 61, 79,  5,  5 ,-5};//赤、黄、青、緑、黒　各色のR基準値
	int gbase[5] = { 11, 73, 34, 29 ,-1};//赤、黄、青、緑、黒　各色のG基準値
	int bbase[5] = {  4,  5, 47,  7 ,-5};//赤、黄、青、緑、黒　各色のG基準値
	int rresult[5];//赤、黄、青、緑、黒　各色のR基準値との差
	int gresult[5];//赤、黄、青、緑、黒　各色のG基準値との差
	int bresult[5];//赤、黄、青、緑、黒　各色のG基準値との差
	int result[5];//赤、黄、青、緑、黒　各色の基準値との差の合計
	

	rgb_val.r = (rgb_val.r > 250) ? 250 : rgb_val.r;
	rgb_val.g = (rgb_val.g > 250) ? 250 : rgb_val.g;
	rgb_val.b = (rgb_val.b > 250) ? 250 : rgb_val.b;
	
	m_log[0] = rgb_val.r;
	m_log[1] = rgb_val.g;
	m_log[2] = rgb_val.b;

	for (int i = 0; i <5; i++){
		if (rbase[i]<=rgb_val.r){
			rresult[i]=rgb_val.r-rbase[i];
		}
		else{
			rresult[i]=rbase[i]-rgb_val.r;
		}
	}

	for (int w = 0; w <5; w++){
		if (gbase[w]<=rgb_val.g){
			gresult[w]=rgb_val.g-gbase[w];
		}
		else{
    		gresult[w]=gbase[w]-rgb_val.g;
		}
	}

	for (int q = 0; q <5; q++){
		if (bbase[q]<=rgb_val.b){
			bresult[q]=rgb_val.b-bbase[q];
		}
		else{
			bresult[q]=bbase[q]-rgb_val.b;
		}
	}

	for (int y = 0; y < 5; y++){
		result[y]=rresult[y]+gresult[y]+bresult[y];
	}
	
	if (m_UnecidedDegree>=result[0]){
		m_UnecidedDegree=result[0];
		m_ColorDistinguish = Color::Red;
	}
	if (m_UnecidedDegree>=result[1]){
		m_UnecidedDegree=result[1];
		m_ColorDistinguish = Color::Yellow;
	}
	if (m_UnecidedDegree>=result[2]){
		m_UnecidedDegree=result[2];
		m_ColorDistinguish = Color::Blue;
	}
	if (m_UnecidedDegree>=result[3]){
		m_UnecidedDegree=result[3];
		m_ColorDistinguish = Color::Green;
	}
	if (m_UnecidedDegree>=result[4]){
		m_UnecidedDegree=result[4];
		m_ColorDistinguish = Color::Black;
	}

	return m_ColorDistinguish;
	//E)
}

ColorDistinguish::~ColorDistinguish()
{
	//S)
	
	//E)
}

//S)
void ColorDistinguish::log(int &loga, int &logb,int &logc)
{
	loga = m_log[0];
	logb = m_log[1];
	logc = m_log[2];
}
//E)
