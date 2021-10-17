// ˅
#include "DistanceMeter.h"
#include "Motor.h"

using namespace ev3api;
// ˄

DistanceMeter::DistanceMeter(Motor* pLeftMotor, Motor* pRightMotor)
	// ˅
	:m_SectionMeasure(0),m_preMeasureLeft(0),m_preMeasureRight(0),m_pLeftMotor(pLeftMotor),m_pRightMotor(pRightMotor)
	// ˄
{
	// ˅
	
	// ˄
}

int DistanceMeter::getSectionDistance()
{
	// ˅
	m_SectionMeasure = static_cast<int>(((m_pLeftMotor->getCount() - m_preMeasureLeft) + (m_pRightMotor->getCount() - m_pRightMotor)) / 2);
	return m_SectionMeasure;
	// ˄
}

void DistanceMeter::resetMeasure()
{
	// ˅
	m_preMeasureLeft = m_pLeftMotor->getCount();
	m_preMeasureRight = m_pRightMotor->getCount();
	// ˄
}

DistanceMeter::~DistanceMeter()
{
	// ˅
	
	// ˄
}

// ˅

// ˄
