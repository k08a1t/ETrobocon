//S)
//Copyright (c) 2016 Kagaku No Yousei. All Rights Reserved.
#include "HSLMeasure.h"

#include "ColorSensor.h"

using namespace ev3api;
//E)

HSLMeasure::HSLMeasure(ColorSensor* pColorSensor)
//S)
  
//E)
{
	//S)
	m_pColorSensor = pColorSensor;
	//E)
}

int HSLMeasure::HSL_Decision(int times)
{
	Times = times;

	rgb_raw_t rgb_val;
	m_pColorSensor->getRawColor(rgb_val);
	int r = rgb_val.r;
	int g = rgb_val.g;
	int b = rgb_val.b;

	/*-------------------------------------*/
	char HSL_H[30];
	sprintf(HSL_H, "r_value = %d", r + 10000);
	ev3_lcd_draw_string(HSL_H, 0, 24);

	char HSL_S[30];
	sprintf(HSL_S, "g_value = %d", g + 10000);
	ev3_lcd_draw_string(HSL_S, 0, 36);

	char HSL_L[30];
	sprintf(HSL_L, "b_value = %d", b + 10000);
	ev3_lcd_draw_string(HSL_L, 0, 48);
	/*-------------------------------------*/

	
	if (Times == 1) {
		Sort[0] = r;
		Sort[1] = g;
		Sort[2] = b;
	}
	else if (Times == 2) {
		float H = 0, S = 0, L = 0;

		Sort[0] = (Sort[0] + r) / 2;
		Sort[1] = (Sort[1] + g) / 2;
		Sort[2] = (Sort[2] + b) / 2;

		for (int s = 0; s < 2; s++) {
			for (int t = s + 1; t < 3; t++) {
				if (Sort[t] > Sort[s]) {
					int tmp = Sort[t];
					Sort[t] = Sort[s];
					Sort[s] = tmp;
				}
			}
		}

		int Result[3] = { 0 };
		/*-----HÇãÅÇﬂÇÈ-----*/
		if (r > g && r > b) {
			H = g - b;
			H = H / (Sort[0] - Sort[2]);
			H = 60 * H;
		}
		else if (g > r && g > b) {
			H = b - r;
			H = H / (Sort[0] - Sort[2]);
			H = 60 * H;
			H = H + 120;
		}
		else if (b > r && b > g) {
			H = r - g;
			H = H / (Sort[0] - Sort[2]);
			H = 60 * H;
			H = H + 240;
		}
		else if (r == g && r == b && g == b) {
			H = 0;
		}

		Result[0] = static_cast<int>(H);

		/*-----SÇãÅÇﬂÇÈ-----*/
		S = Sort[0] - Sort[2];

		Result[1] = static_cast<int>(S);

		/*-----LÇãÅÇﬂÇÈ-----*/
		L = Sort[2] + Sort[0];
		L = L / 2;

		Result[2] = static_cast<int>(L);

		/*-------------------------------------*/
		char S_HH[30];
		sprintf(S_HH, "H_value = %d", Result[0] + 10000);
		ev3_lcd_draw_string(S_HH, 0, 72);

		char S_SS[30];
		sprintf(S_SS, "S_value = %d", Result[1] + 10000);
		ev3_lcd_draw_string(S_SS, 0, 84);

		char S_LL[30];
		sprintf(S_LL, "L_value = %d", Result[2] + 10000);
		ev3_lcd_draw_string(S_LL, 0, 96);
		/*-------------------------------------*/

		Result_HSL = (Result[0] * 1000000) + (Result[1] * 1000) + Result[2];

		/*-------------------------------------*/
		char Result_HSL_Num[30];
		sprintf(Result_HSL_Num, "L_value = %d", Result_HSL);
		ev3_lcd_draw_string(Result_HSL_Num, 0, 120);
		/*-------------------------------------*/

		return Result_HSL;
	}
}

HSLMeasure::~HSLMeasure()
{
	//S)
	
	//E)
}

//S)

//E)
