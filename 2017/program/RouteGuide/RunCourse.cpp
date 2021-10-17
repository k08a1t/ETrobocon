//S)
#include "RunCourse.h"

#include "../Measure/Calibration.h"
#include "../Communication/Communication.h"

using namespace ev3api;
//E)

bool RunCourse::startRun()
{
	//S)
	if (m_pRunArea_list[m_current_index]->start() == true){
		m_current_index++;
	}
	if (m_list_num <= m_current_index){
		m_current_index = 0;
		return true;
	}
	else {
		return false;
	}
	//E)
}

void RunCourse::prepareRun()
{
	//S)
	m_pCalibration-> calibrate();
	//E)
}

void RunCourse::addRunArea(RunArea* pArea)
{
	//S)
	m_pRunArea_list[m_list_num] = pArea;
	m_list_num++;
	//E)
}

RunCourse::RunCourse(Calibration* pCalibration, Communication* pCommunication)
//S)
:m_now_area_number(0),m_current_index(0),m_list_num(0),m_pCalibration(pCalibration),m_pCommunication(pCommunication)
//E)
{
	//S)
	
	//E)
}

RunCourse::~RunCourse()
{
	//S)
	
	//E)
}

//S)

//E)
