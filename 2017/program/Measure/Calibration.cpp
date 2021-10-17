//S)
#include "Calibration.h"
#include "HSLMeasure.h"

#include "Clock.h"
#include "GyroSensor.h"
#include "ColorSensor.h"
#include "TouchSensor.h"

using namespace ev3api;

static int border;
//E)

void Calibration::calibrate()
{
	//S)

	hslCalibration();
	Display_Clean();
	ResultHSL_Check();
	Display_Clean();

	m_black = calBrightness();
	ev3_speaker_play_tone(NOTE_C5, 100);
	char BLACK[16];
	sprintf(BLACK, "black = %d", m_black);
	ev3_lcd_draw_string(BLACK, 0, 0);
	m_pClock->wait(100);
	
	m_white = calBrightness();
	ev3_speaker_play_tone(NOTE_C5, 100);
	char WHITE[16];
	sprintf(WHITE, "white = %d", m_white);
	ev3_lcd_draw_string(WHITE, 0, 12);
	m_pClock->wait(100);
	
	m_gray = calBrightness();
	char GRAY[16];
	sprintf(GRAY, "gray = %d", m_gray);
	ev3_lcd_draw_string(GRAY, 0, 24);

	border = 33;//static_cast<int>((m_black + m_white + m_gray)/3 );
	char BORDER[16];
	sprintf(BORDER, "border = %d", border);
	ev3_lcd_draw_string(BORDER, 0, 36);

	char BATTERYMA[32];
	char BATTERYMV[32];
	int Battery_mA = ev3_battery_current_mA();
	int Battery_mV = ev3_battery_voltage_mV();
	sprintf(BATTERYMA, "Battery_mA = %d", Battery_mA);
	ev3_lcd_draw_string(BATTERYMA, 0, 60);
	sprintf(BATTERYMV, "Battery_mV = %d", Battery_mV);
	ev3_lcd_draw_string(BATTERYMV, 0, 72);

	m_pGyroSensor->reset();
	ev3_speaker_play_tone(NOTE_C5, 100);
	m_pClock->wait(100);
	m_pBrightness->setBorder(border);

	while (!m_pTouchSensor->isPressed());

	ev3_speaker_play_tone(NOTE_C5, 100);
	m_pClock->wait(100);
	//E)
}

Calibration::Calibration(TouchSensor* pTouchSensor, ColorSensor* pColorSensor, Clock* pClock, GyroSensor* pGyroSensor, Brightness* pBrightness, HSLMeasure* pHSLMeasure)
//S)
: m_black(0),m_white(0),m_gray(0),m_pColorSensor(pColorSensor),m_pGyroSensor(pGyroSensor),m_pClock(pClock),m_pTouchSensor(pTouchSensor),m_pBrightness(pBrightness),m_pHSLMeasure(pHSLMeasure)
//E)
{
	//S)
	
	//E)
}

int Calibration::getBlack()
{
	//S)
	return m_black;
	//E)
}

int Calibration::getWhite()
{
	//S)
	return m_white;
	//E)
}

int Calibration::getGray()
{
	//S)
	return m_gray;
	//E)
}

int Calibration::getBorder()
{
	//S)
	return border;
	//E)
}

unsigned int Calibration::getHSL_Red()
{
	return HSL_Red;
}

unsigned int Calibration::getHSL_Yellow()
{
	return HSL_Yellow;
}

unsigned int Calibration::getHSL_Blue()
{
	return HSL_Blue;
}

unsigned int Calibration::getHSL_Green()
{
	return HSL_Green;
}

int Calibration::calBrightness()
{
	//S)
	int point = 0;

	while(!m_pTouchSensor->isPressed());

	
	for(int i = 0; i <= 99; i++) {
		point += m_pColorSensor->getBrightness();
		m_pClock->wait(1);
	}

	point = point/100;

	m_pClock->wait(500);

	return point;
	//E)
}

void Calibration::rgbCalibration()
{
	//S)
	while(!m_pTouchSensor->isPressed()){
		rgb_raw_t rgb;
		m_pColorSensor->getRawColor(rgb);  
	
		char R_value[16];
		sprintf(R_value, "R_value = %d",rgb.r + 10000 );
		ev3_lcd_draw_string(R_value, 0, 0);

		char G_value[16];
		sprintf(G_value, "G_value = %d",rgb.g + 10000 );
		ev3_lcd_draw_string(G_value, 0, 12);

		char B_value[16];
		sprintf(B_value, "B_value = %d",rgb.b + 10000 );
		ev3_lcd_draw_string(B_value, 0, 24);
	}
	ev3_speaker_play_tone(NOTE_C5, 100);
	m_pClock->wait(500);

	char Display_Clean[30];
	sprintf(Display_Clean, "                    ");
	ev3_lcd_draw_string(Display_Clean, 0, 0);
	ev3_lcd_draw_string(Display_Clean, 0, 12);
	ev3_lcd_draw_string(Display_Clean, 0, 24);
}

void Calibration::hslCalibration()
{
	char Display[30];

	//Ô
	ev3_speaker_play_tone(NOTE_B6, 100);
	while (!m_pTouchSensor->isPressed()) {
		m_pHSLMeasure->HSL_Decision(1);
		sprintf(Display, "Red_1");
		ev3_lcd_draw_string(Display, 0, 12);
	}
	ev3_speaker_play_tone(NOTE_C5, 100);
	m_pClock->wait(1000);
	ev3_speaker_play_tone(NOTE_B6, 100);
	while (!m_pTouchSensor->isPressed()) {
		HSL_Red = m_pHSLMeasure->HSL_Decision(2);
		sprintf(Display, "Red_2");
		ev3_lcd_draw_string(Display, 0, 12);
	}
	Display_Clean();
	ev3_speaker_play_tone(NOTE_C5, 100);
	m_pClock->wait(1000);

	//‰©F
	ev3_speaker_play_tone(NOTE_B6, 100);
	while (!m_pTouchSensor->isPressed()) {
		m_pHSLMeasure->HSL_Decision(1);
		sprintf(Display, "Yellow_1    ");
		ev3_lcd_draw_string(Display, 0, 12);
	}
	ev3_speaker_play_tone(NOTE_C5, 100);
	m_pClock->wait(1000);
	ev3_speaker_play_tone(NOTE_B6, 100);
	while (!m_pTouchSensor->isPressed()) {
		HSL_Yellow = m_pHSLMeasure->HSL_Decision(2);
		sprintf(Display, "Yellow_2    ");
		ev3_lcd_draw_string(Display, 0, 12);
	}
	Display_Clean();
	ev3_speaker_play_tone(NOTE_C5, 100);
	m_pClock->wait(1000);

	//Â
	ev3_speaker_play_tone(NOTE_B6, 100);
	while (!m_pTouchSensor->isPressed()) {
		m_pHSLMeasure->HSL_Decision(1);
		sprintf(Display, "Blue_1    ");
		ev3_lcd_draw_string(Display, 0, 12);
	}
	ev3_speaker_play_tone(NOTE_C5, 100);
	m_pClock->wait(1000);
	ev3_speaker_play_tone(NOTE_B6, 100);
	while (!m_pTouchSensor->isPressed()) {
		HSL_Blue = m_pHSLMeasure->HSL_Decision(2);
		sprintf(Display, "Blue_2    ");
		ev3_lcd_draw_string(Display, 0, 12);
	}
	Display_Clean();
	ev3_speaker_play_tone(NOTE_C5, 100);
	m_pClock->wait(1000);

	//—Î
	ev3_speaker_play_tone(NOTE_B6, 100);
	while (!m_pTouchSensor->isPressed()) {
		m_pHSLMeasure->HSL_Decision(1);
		sprintf(Display, "Green_1    ");
		ev3_lcd_draw_string(Display, 0, 12);
	}
	ev3_speaker_play_tone(NOTE_C5, 100);
	m_pClock->wait(1000);
	ev3_speaker_play_tone(NOTE_B6, 100);
	while (!m_pTouchSensor->isPressed()) {
		HSL_Green = m_pHSLMeasure->HSL_Decision(2);
		sprintf(Display, "Green_2    ");
		ev3_lcd_draw_string(Display, 0, 12);
	}
	Display_Clean();
	ev3_speaker_play_tone(NOTE_C5, 100);
	m_pClock->wait(1000);
}

void Calibration::Display_Clean()
{
	char Display_Clean[40];
	sprintf(Display_Clean, "                                       ");
	ev3_lcd_draw_string(Display_Clean, 0, 12);
	ev3_lcd_draw_string(Display_Clean, 0, 24);
	ev3_lcd_draw_string(Display_Clean, 0, 36);
	ev3_lcd_draw_string(Display_Clean, 0, 48);
	ev3_lcd_draw_string(Display_Clean, 0, 60);
	ev3_lcd_draw_string(Display_Clean, 0, 72);
	ev3_lcd_draw_string(Display_Clean, 0, 84);
	ev3_lcd_draw_string(Display_Clean, 0, 96);
	ev3_lcd_draw_string(Display_Clean, 0, 108);
	ev3_lcd_draw_string(Display_Clean, 0, 120);
}

void Calibration::ResultHSL_Check()
{
	while (!m_pTouchSensor->isPressed()) {
		char HSL_Red_Result[30];
		sprintf(HSL_Red_Result, "HSL_Red_Result = %d", HSL_Red);
		ev3_lcd_draw_string(HSL_Red_Result, 0, 12);

		char HSL_Yellow_Result[16];
		sprintf(HSL_Yellow_Result, "HSL_Yellow_Result = %d", HSL_Yellow);
		ev3_lcd_draw_string(HSL_Yellow_Result, 0, 24);

		char HSL_Blue_Result[16];
		sprintf(HSL_Blue_Result, "HSL_Blue_Result = %d", HSL_Blue);
		ev3_lcd_draw_string(HSL_Blue_Result, 0, 36);

		char HSL_Green_Result[16];
		sprintf(HSL_Green_Result, "HSL_Green_Result = %d", HSL_Green);
		ev3_lcd_draw_string(HSL_Green_Result, 0, 48);
	}
	m_pClock->wait(500);
}

Calibration::~Calibration()
{
	//S)
	
	//E)
}

//S)

//E)
