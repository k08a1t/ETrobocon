//S)
#include "Motor.h"
using namespace ev3api;
//E)

#ifndef RUNMETHOD_RUNMETHOD_H
#define RUNMETHOD_RUNMETHOD_H

//S)

//E)

class RunMethod
{
	//S)
	
	//E)

protected:

	Motor* m_pLeftMotor;

	Motor* m_pRightMotor;

public:

	RunMethod();

	virtual void run() = 0;

	virtual ~RunMethod();

	//S)
	
	//E)
};

//S)

//E)

#endif	// RUNMETHOD_RUNMETHOD_H

//S)

//E)
