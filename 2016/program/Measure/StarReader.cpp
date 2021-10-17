//S)
#include "StarReader.h"

#include "ColorSensor.h"

using namespace ev3api;
//E)

StarReader::StarReader(ColorSensor* pColorSensor)
//S)
	: m_star_color(1),m_judge(1000),m_pColorSensor(pColorSensor)
//E)
{
	//S)
	
	//E)
}

void StarReader::readStarSituation()
{
	//S)
		checkStarColor();
	//E)
}

int StarReader::getStarSituation()
{
	//S)
		return m_star_color;
	//E)
}

void StarReader::checkStarColor()
{
	//S)
	rgb_raw_t rgb_val;
	m_pColorSensor->getRawColor(rgb_val);
	int rbase[4] = { 147, 148,  23,  26 };//赤、黄、青、緑
	int gbase[4] = {  85, 277, 145, 138 };//赤、黄、青、緑
	int bbase[4] = {  45,  45, 200,  55 };//赤、黄、青、緑
	int rresult[4];
	int gresult[4];
	int bresult[4];
	int result[4];
	


	for (int i = 0; i <4; i++){
		if (rbase[i]<=rgb_val.r){
			rresult[i]= rgb_val.r-rbase[i];
		}
		else{
			rresult[i]=rbase[i]- rgb_val.r;
		}
	}

	for (int w = 0; w <4; w++){
		if (gbase[w]<= rgb_val.g){
			gresult[w]= rgb_val.g-gbase[w];
		}
		else{
    		gresult[w]=gbase[w]- rgb_val.g;
		}
	}

	for (int q = 0; q <4; q++){
		if (bbase[q]<= rgb_val.b){
			bresult[q]= rgb_val.b-bbase[q];
		}
		else{
			bresult[q]=bbase[q]- rgb_val.b;
		}
	}

	for (int y = 0; y < 4; y++){
		result[y]=rresult[y]+gresult[y]+bresult[y];
	}
	
	if (m_judge>=result[0]){
		m_judge=result[0];
		m_star_color=1;
	}
	if (m_judge>=result[1]){
		m_judge=result[1];
		m_star_color=2;
	}
	if (m_judge>=result[2]){
		m_judge=result[2];
		m_star_color=3;
	}
	if (m_judge>=result[3]){
		m_judge=result[3];
		m_star_color=4;
	}
	//E)
}

StarReader::~StarReader()
{
	//S)
	
	//E)
}

//S)

//E)
