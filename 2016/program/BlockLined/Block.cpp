//S)
#include "Block.h"

#include "BlockLined/ColorDistinguish.h"
#include "BlockLined/MovementType.h"
#include "BlockLined/Color.h"
//#include "ColorSensor.h"
//using namespace ev3api;
//E)

Block::Block(Color t_Color, ColorDistinguish* pColorDistinguish, int number)
//S)
       :m_Color(t_Color),m_Arrangement(false),m_MovementAdvisability(UnJudgement),m_Number(number),m_pColorDistinguish(pColorDistinguish)
//E)
{
	//S)
	
	//E)
}

void Block::SearchColor()
{
	//S)
	 m_Color = m_pColorDistinguish -> BlockcolorDistinguish();//ブロックの色を調べてもらう

	 if(m_Color == Black){//黒だったら移動禁止にして、配置済みにする。
		m_MovementAdvisability = MovementProhibition;
		m_Arrangement = true;
	}
	else{
		m_MovementAdvisability = MovementPossibility;
		m_Arrangement = false;
	}


	//E)
}

Color Block::ObtainmentColor()
{
	//S)
	return m_Color;
	//E)
}

void Block::setArrangementComplete()
{
	//S)
	m_Arrangement = true;	   
	//E)
}

bool Block::getArrangement()
{
	//S)
    return m_Arrangement;
	//E)
}

MovementType Block::getMovementAdvisability()
{
	//S)
	return m_MovementAdvisability;
	//E)
}

int Block::getBlockNumber()
{
	//S)
	return m_Number;
	//E)
}

Block::~Block()
{
	//S)
	
	//E)
}

void Block::LCDcolorout()
{
	//S)
	switch(m_Color){
		case Red:
			ev3_led_set_color (LED_RED);
			break;
		case Blue:
			ev3_led_set_color (LED_OFF);
			break;
		case Green:
			ev3_led_set_color (LED_GREEN);
			break;
		case Yellow:
			ev3_led_set_color (LED_ORANGE);
			break;
		case Black:
			break;
		default:
			break;
	}

	//E)
}

//S)

//E)
