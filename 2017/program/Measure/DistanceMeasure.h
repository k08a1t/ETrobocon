//S)
//Copyright (c) 2015 Kagaku No Yousei. All Rights Reserved.
//E)

#ifndef MEASURE_DISTANCEMEASURE_H
#define MEASURE_DISTANCEMEASURE_H

//S)
#include "Motor.h"

using namespace ev3api;
//E)

class DistanceMeasure
{
	//S)
	
	//E)

private:

	int m_allMeasure;

	int m_BlockMeasure;

	int m_preMeasureLeft;

	int m_preMeasureRight;

	Motor* m_pLeftMotor;

	Motor* m_pRightMotor;

public:

	DistanceMeasure(Motor* pLeftMotor, Motor* pRightMotor);

	int getAll();

	void resetAll();

	int getBlock();

	void resetBlock();

	int getBlockLeft();

	int getBlockRight();

	int getDirection();

	~DistanceMeasure();

	//S)
	
	//E)
};

//S)

//E)

#endif	// MEASURE_DISTANCEMEASURE_H

//S)

//E)
