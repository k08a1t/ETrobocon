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

	if (m_TF == true) {
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


	if (5 < H && H < 15) {
		return true;//red
	}
	else if (22 < H && H < 32) {
		return true;//yellow
	}
	else if (186 < H && H < 196) {
		return true;//blue
	}
	else if (119 < H && < H < 129) {
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
