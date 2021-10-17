//S)
#include "Brightness.h"
//E)

Brightness::Brightness(ColorSensor* pColorSensor)
//S)
:	m_border(0),m_revision_brightness(0)	
//E)
{
	//S)
	m_pColorSensor = pColorSensor;
	//E)
}

int Brightness::getBrightness()
{
	//S)
	return m_pColorSensor->getBrightness()-m_border;
	//E)
}

void Brightness::setBorder(int border)
{
	//S)
	m_border = border;
	//E)
}

Brightness::~Brightness()
{
	//S)
	
	//E)
}

//S)

//E)
