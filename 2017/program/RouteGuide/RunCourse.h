//S)

//E)

#ifndef ROUTEGUIDE_RUNCOURSE_H
#define ROUTEGUIDE_RUNCOURSE_H

//S)
#include "RouteGuide/RunArea.h"
#include "../Measure/Calibration.h"

using namespace ev3api;
//E)

class RunCourse
{
	//S)
	
	//E)

private:

	int m_now_area_number;

	int m_current_index;

	int m_list_num;

	RunArea* m_pRunArea_list[10];

	RunArea* m_pRunArea;

	Calibration* m_pCalibration;

	Communication* m_pCommunication;

public:

	bool startRun();

	void prepareRun();

	void addRunArea(RunArea* pArea);

	RunCourse(Calibration* pCalibration, Communication* pCommunication);

	~RunCourse();

	//S)
	
	//E)
};

//S)

//E)

#endif	// ROUTEGUIDE_RUNCOURSE_H

//S)

//E)
