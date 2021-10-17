//S)

//E)

#ifndef RUNMETHOD_LINETRACEMETHOD_H
#define RUNMETHOD_LINETRACEMETHOD_H

//S)
#include "RunMethod/RunMethod.h"
#include "Measure/Calibration.h"
#include "RunMethod/PID.h"
#include "ColorSensor.h"
#include "Motor.h"

using namespace ev3api;
//E)

class LineTraceMethod : public RunMethod
{
	//S)
	
	//E)

private:

	int m_speed;

	int m_turn_MAX;

	bool m_edge;

	int m_border_change;

	Brightness* m_pBrightness;

	PID* m_pPID;

public:

	LineTraceMethod(int speed, int max, bool edge, int borderChange, Brightness* pBrightness, PID* pPID, Motor* pLeftMotor, Motor* pRightMotor);

	void run();

	~LineTraceMethod();

	//S)
	
	//E)
};

//S)

//E)

#endif	// RUNMETHOD_LINETRACEMETHOD_H

//S)

//E)
