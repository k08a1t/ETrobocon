//S)
#include "Calibration.h"

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

	rgbCalibration();

	m_black = calBrightness();
	ev3_speaker_play_tone(NOTE_C5, 100);
	char BLACK[16];
	sprintf(BLACK, "black = %d", m_black);
	ev3_lcd_draw_string(BLACK, 0, 12);
	m_pClock->wait(100);
	
	m_white = calBrightness();
	ev3_speaker_play_tone(NOTE_C5, 100);
	char WHITE[16];
	sprintf(WHITE, "white = %d", m_white);
	ev3_lcd_draw_string(WHITE, 0, 24);
	m_pClock->wait(100);
	
	m_gray = calBrightness();
	char GRAY[16];
	sprintf(GRAY, "gray = %d", m_gray);
	ev3_lcd_draw_string(GRAY, 0, 36);

	border = static_cast<int>((m_black + m_white + m_gray)/3 );
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
	while(!m_pTouchSensor->isPressed());
	//E)
}

Calibration::Calibration(TouchSensor* pTouchSensor, ColorSensor* pColorSensor, Clock* pClock, GyroSensor* pGyroSensor, Brightness* pBrightness)
//S)
: m_black(0),m_white(0),m_gray(0),m_pColorSensor(pColorSensor),m_pGyroSensor(pGyroSensor),m_pClock(pClock),m_pTouchSensor(pTouchSensor),m_pBrightness(pBrightness)
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
		sprintf(R_value, "R_value = %d",rgb.r+10000 );
		ev3_lcd_draw_string(R_value, 0, 0);

		char G_value[16];
		sprintf(G_value, "G_value = %d",rgb.g+10000 );
		ev3_lcd_draw_string(G_value, 0, 12);

		char B_value[16];
		sprintf(B_value, "B_value = %d",rgb.b+10000 );
		ev3_lcd_draw_string(B_value, 0, 24);

		m_pClock->wait(500);
	}
	
	//E)
}

Calibration::~Calibration()
{
	//S)
	
	//E)
}

//S)

//E)
