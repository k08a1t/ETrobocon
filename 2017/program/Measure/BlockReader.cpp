//S)
#include "BlockReader.h"

#include "ColorSensor.h"

using namespace ev3api;
//E)

BlockReader::BlockReader(ColorSensor* pColorSensor)
//S)
	: m_Block_color(1),m_pColorSensor(pColorSensor)
//E)
{
	//S)
	
	//E)
}

void BlockReader::readBlockSituation()
{
	//S)
		checkBlockColor();
	//E)
}

int BlockReader::getBlockSituation()
{
	//S)
		return m_Block_color;
	//E)
}

void BlockReader::checkBlockColor()
{
	//S)
	rgb_raw_t rgb_val;
	m_pColorSensor->getRawColor(rgb_val);
	int r = rgb_val.r;
	int g = rgb_val.g;
	int b = rgb_val.b;

	int Sort[3] = { 0 };
	float H = 0;

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

	/*-----H‚ð‹‚ß‚é-----*/
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


	if (0 < H && H < 10) {
		m_Block_color = 1;//red
	}
	else if (40 < H && H < 60) {
		m_Block_color = 2;//yellow
	}
	else if (190 < H && H < 210) {
		m_Block_color = 3;//blue
	}
	else if (110 < H && H < 130) {
		m_Block_color = 4;//green
	}

	//E)
}

BlockReader::~BlockReader()
{
	//S)
	
	//E)
}

//S)

//E)
