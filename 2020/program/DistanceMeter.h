// ˅

// ˄

#ifndef DISTANCEMETER_H_
#define DISTANCEMETER_H_

// ˅
class Motor;


// ˄

class DistanceMeter
{
	// ˅
	
	// ˄

private:

	int m_SectionMeasure;

	int m_preMeasureRight;

	int m_preMeasureLeft;

	Motor* m_pLeftMotor;

	Motor* m_pRightMotor;

public:

	DistanceMeter(Motor* pLeftMotor, Motor* pRightMotor);

	int getSectionDistance();

	void resetMeasure();

	~DistanceMeter();

	// ˅
public:
	
protected:
	
private:
	DistanceMeter(const DistanceMeter&) = delete;
	DistanceMeter& operator=(const DistanceMeter&) = delete;
	
	// ˄
};

// ˅

// ˄

#endif	// DISTANCEMETER_H_

// ˅

// ˄
