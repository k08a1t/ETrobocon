//S)
//Copyright (c) 2016 Kagaku No Yousei. All Rights Reserved.
#include "DistanceMeasure.h"

#include "Motor.h"

using namespace ev3api;
//E)

DistanceMeasure::DistanceMeasure(Motor* pLeftMotor, Motor* pRightMotor)
//S)
  : m_allMeasure(0)
  , m_BlockMeasure(0)
  , m_preMeasureLeft(0)
  , m_preMeasureRight(0)
  
//E)
{
	//S)
	m_pLeftMotor = pLeftMotor;
	m_pRightMotor = pRightMotor;
	//E)
}

int DistanceMeasure::getAll()
{
	//S)
	m_allMeasure = static_cast<int>( (m_pLeftMotor->getCount() + m_pRightMotor->getCount())/2 );
	m_allMeasure = (int)(m_allMeasure * 0.7);
	return m_allMeasure;
	//E)
}

void DistanceMeasure::resetAll()
{
	//S)
	m_pLeftMotor->setCount(0);
	m_pRightMotor->setCount(0);
	m_allMeasure = 0;
	m_BlockMeasure = 0;
	m_preMeasureLeft = 0;
	m_preMeasureRight = 0;

	return;
	//E)
}

int DistanceMeasure::getBlock()
{
	//S)
	m_BlockMeasure = static_cast<int>(((m_pLeftMotor->getCount() - m_preMeasureLeft)+(m_pRightMotor->getCount() - m_preMeasureRight))/2);
	m_BlockMeasure = (int)(m_BlockMeasure * 0.7);
	return m_BlockMeasure;
	//E)
}

void DistanceMeasure::resetBlock()
{
	//S)
	m_preMeasureLeft = m_pLeftMotor->getCount();
	m_preMeasureRight = m_pRightMotor->getCount();

	return;
	//E)
}

int DistanceMeasure::getBlockLeft()
{
	//S)
	int measure;
	measure = (m_pLeftMotor->getCount() - m_preMeasureLeft);
	measure = (int)(measure * 0.7);
	return measure;
	//E)
}

int DistanceMeasure::getBlockRight()
{
	//S)
	int measure;
	measure = (m_pRightMotor->getCount() - m_preMeasureRight);
	measure = (int)(measure * 0.7);
	return measure;
	//E)
}

int DistanceMeasure::getDirection()
{
	//S)
	int direction = m_pLeftMotor->getCount() - m_pRightMotor->getCount();
	return direction;
	
	//E)
}

DistanceMeasure::~DistanceMeasure()
{
	//S)
	
	//E)
}

//S)

//E)
