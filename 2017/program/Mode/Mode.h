//S)

//E)

#ifndef MODE_MODE_H
#define MODE_MODE_H

//S)
#include "Motor.h"
#include "Clock.h"

using namespace ev3api;
//E)

class Mode
{
	//S)
	
	//E)

private:

	int m_arm_pos;

	int m_i_valu;

	Motor* m_pArmMotor;

	Clock* m_pClock;

public:

	Mode(int arm_pos, Motor* pArmMotor, Clock* pClock);

	void decideMede();

	void preMode();

	~Mode();

	//S)
	
	//E)
};

//S)

//E)

#endif	// MODE_MODE_H

//S)

//E)
