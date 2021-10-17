//S)
#include "PBPlaceDetectionCondition.h"
#include "Measure/Calibration.h"
#include "ColorSensor.h"

using namespace ev3api;
//E)

PBPlaceDetectionCondition::PBPlaceDetectionCondition(ColorSensor* pColorSensor, bool TF, Calibration* pCalibration)
//S)
	: m_TF(TF), m_Result_TF(nullptr), m_pCalibration(pCalibration)
//E)
{
	//S)
	m_pColorSensor = pColorSensor;
	//E)
}

bool PBPlaceDetectionCondition::isSatisfy()
{
	//S)
	setDecisionBorder();

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
		if (Red[2] - 20 < H && H < Red[2] + 20 && L > 70 && S < Red[0] + 30 && S > Red[0] - 30) {
			//red
			m_Result_TF = true;
		}
		else if (Yellow[2] - 20 < H && H < Yellow[2] + 20 && L > 70 && S < Yellow[0] + 30 && S > Yellow[0] - 30) {
			//yellow
			m_Result_TF = true;
		}
		else if (Blue[2] - 20 < H && H < Blue[2] + 20 && L > 70 && S < Blue[0] + 30 && S > Blue[0] - 30) {
			//blue
			m_Result_TF = true;
		}
		else if (Green[2] - 20 < H && H < Green[2] + 20 && L > 70 && S < Green[0] + 30 && S > Green[0] - 30) {
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

void PBPlaceDetectionCondition::setDecisionBorder()
{
	//ê‘
	unsigned int Material_Red;
	unsigned int Material_Yellow;
	unsigned int Material_Blue;
	unsigned int Material_Green;
	Material_Red = m_pCalibration->getHSL_Red();
	Material_Yellow = m_pCalibration->getHSL_Yellow();
	Material_Blue = m_pCalibration->getHSL_Blue();
	Material_Green = m_pCalibration->getHSL_Green();
	for (int a = 0; a < 3; a++) {
		Red[a] = Material_Red % 1000;
		Material_Red = (Material_Red - Red[a]) / 1000;
		Yellow[a] = Material_Yellow % 1000;
		Material_Yellow = (Material_Yellow - Yellow[a]) / 1000;
		Blue[a] = Material_Blue % 1000;
		Material_Blue = (Material_Blue - Blue[a]) / 1000;
		Green[a] = Material_Green % 1000;
		Material_Green = (Material_Green - Green[a]) / 1000;
	}
}

PBPlaceDetectionCondition::~PBPlaceDetectionCondition()
{
	//S)
	
	//E)
}

//S)
void PBPlaceDetectionCondition::log(int &loga, int &logb,int &logc)
{
	loga = m_log[0];
	logb = m_log[1];
	logc = m_log[2];
}
//E)
