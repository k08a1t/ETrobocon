//S)
#include "RailDetectionCondition.h"
#include "ColorSensor.h"

using namespace ev3api;
//E)

RailDetectionCondition::RailDetectionCondition(ColorSensor* pColorSensor, bool TF)
//S)
	: m_TF(TF), m_Result_TF(nullptr)
//E)
{
	//S)
	m_pColorSensor = pColorSensor;
	//E)
}

bool RailDetectionCondition::isSatisfy()
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
	
	/*-----H�����߂�-----*/
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

	/*-----S�����߂�-----*/
	S = Sort[0] - Sort[2];

	/*-----L�����߂�-----*/
	L = Sort[2] + Sort[0];
	L = L / 2;
	/*-----Bluetooth-----*/
	m_log[0] = H;
	m_log[1] = S;
	m_log[2] = L;
	
	if (m_TF == true) {
		if (170 < H && H < 200 && L > 40 && S > 40) {
			m_Result_TF = true;//blue
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

RailDetectionCondition::~RailDetectionCondition()
{
	//S)
	
	//E)
}

//S)
void RailDetectionCondition::log(int &loga, int &logb,int &logc)
{
	loga = m_log[0];
	logb = m_log[1];
	logc = m_log[2];
}
//E)