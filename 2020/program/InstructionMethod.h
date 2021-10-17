// ˅

// ˄

#ifndef INSTRUCTIONMETHOD_H_
#define INSTRUCTIONMETHOD_H_

// ˅
#include "RunMethod.h"

class Motor;


// ˄

class InstructionMethod : public RunMethod
{
	// ˅
	
	// ˄

private:

	int m_right_speed;

	int m_left_speed;

	Motor* m_pLeftMotor;

	Motor* m_pRightMotor;

public:

	InstructionMethod(int speed_L, int speed_R, Motor* pLeftMotor, Motor* pRightMotor);

	void run();

	~InstructionMethod();

	// ˅
public:
	
protected:
	
private:
	InstructionMethod(const InstructionMethod&) = delete;
	InstructionMethod& operator=(const InstructionMethod&) = delete;
	
	// ˄
};

// ˅

// ˄

#endif	// INSTRUCTIONMETHOD_H_

// ˅

// ˄
