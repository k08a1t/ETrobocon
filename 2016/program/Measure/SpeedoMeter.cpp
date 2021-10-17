//S)
#include "SpeedoMeter.h"

#include "Measure/DistanceMeasure.h"

using namespace ev3api;
//E)

SpeedoMeter::SpeedoMeter(DistanceMeasure* pDistanceMeasure)
//S)
:	m_now_speed(0),m_num(0),m_pDistanceMeasure(pDistanceMeasure)
//E)
{
	//S)
	for (int i = 0; i < 11; i++) {
		m_count[i] = 0;
	}
	//E)
}

void SpeedoMeter::update()
{
	//S)
	int distance;
	distance = m_pDistanceMeasure->getAll();
	m_count[m_num]=distance;
	
	int i;
	i=m_num;
	m_num++;
	
	int count = 7;
	if(m_num>=count){
		m_num =0;
	}
	
	m_now_speed = (m_count[i]-m_count[m_num]);
	//E)
}

int SpeedoMeter::get()
{
	//S)
	return m_now_speed;
	//E)
}

SpeedoMeter::~SpeedoMeter()
{
	//S)
	
	//E)
}

//S)

//E)
