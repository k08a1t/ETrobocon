//S)

//E)

#ifndef RUNMETHOD_INSTRUCTIONMETHOD_H
#define RUNMETHOD_INSTRUCTIONMETHOD_H

//S)
#include "RunMethod/RunMethod.h"
#include "Motor.h"
using namespace ev3api;
//E)

class InstructionMethod : public RunMethod
{
	//S)
	
	//E)

private:

	int m_speed_L;

	int m_speed_R;

public:

	InstructionMethod(int speedl, int speedr, Motor* pLeftMotor, Motor* pRightMotor);

	void run();

	~InstructionMethod();

	//S)
	
	//E)
};

//S)

//E)

#endif	// RUNMETHOD_INSTRUCTIONMETHOD_H

//S)

//E)
