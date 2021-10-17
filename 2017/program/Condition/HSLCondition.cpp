//S)
#include "HSLCondition.h"
#include "ColorSensor.h"

using namespace ev3api;
//E)

HSLCondition::HSLCondition(ColorSensor* pColorSensor, bool TF)
//S)
	: m_TF(TF), m_Result_TF(nullptr)
//E)
{
	//S)
	m_pColorSensor = pColorSensor;
	//E)
}

bool HSLCondition::isSatisfy()
{
	//S)
	rgb_raw_t rgb_val;
	m_pColorSensor->getRawColor(rgb_val);
	int r = rgb_val.r;
	int g = rgb_val.g;
	int b = rgb_val.b;

	int Sort[3] = { 0 };
	float H = 0, S = 0, L = 0;

	Sort[0] = r;
	Sort[1] = g;
	Sort[2] = b;

	for (int s = 0; s < 2; s++) {
		for (int t = s + 1; t < 3; t++) {
			if (Sort[t] > Sort[s]) {
				int tmp = Sort[t];
				Sort[t] = Sort[s];
				Sort[s] = tmp;
			}
		}
	}
	
	/*-----HÇãÅÇﬂÇÈ-----*/
	if (r > g && r > b) {
		H = g - b;
		H = H / (Sort[0] - Sort[2]);
		H = H * 60;
	}
	else if (g > r && g > b) {
		H = b - r;
		H = H / (Sort[0] - Sort[2]);
		H = (H * 60) + 120;
	}
	else if (b > r && b > g) {
		H = r - g;
		H = H / (Sort[0] - Sort[2]);
		H = (H * 60) + 240;
	}
	else if (r == g && g == b && b == r) {
		H = 0;
	}

	/*-----SÇãÅÇﬂÇÈ-----*/
	S = Sort[0] - Sort[2];

	/*-----LÇãÅÇﬂÇÈ-----*/
	L = Sort[2] + Sort[0];
	L = L / 2;
	/*-----Bluetooth-----*/
	m_log[0] = H;
	m_log[1] = S;
	m_log[2] = L;
	
	if (m_TF == true) {
		if (0 < H && H < 30 && L > 60 && S < 300 && S > 200) {
			//red
			m_Result_TF = true;
		}
		else if (30 < H && H < 70 && L > 60 && S < 350 && S > 250) {
			//yellow
			m_Result_TF = true;
		}
		else if (170 < H && H < 200 && L > 60 && S < 110 && S > 80) {
			//blue
			m_Result_TF = true;
		}
		else if (100 < H && H < 140 && L > 60 && S < 140 && S > 100) {
			//green
			m_Result_TF = true;
		}
		else {
			m_Result_TF = false;
		}
	}
	else if (m_TF == false) {
		m_Result_TF = false;
	}

	return m_Result_TF;
	//E)
}

HSLCondition::~HSLCondition()
{
	//S)
	
	//E)
}

//S)
void HSLCondition::log(int &loga, int &logb,int &logc)
{
	loga = m_log[0];
	logb = m_log[1];
	logc = m_log[2];
}
//E)
