//S)

//E)

#ifndef CONDITION_PBPLACEDETECTIONCONDITION_H
#define CONDITION_PBPLACEDETECTIONCONDITION_H

//S)
#include "Condition/Condition.h"
#include "Measure/Calibration.h"
#include "ColorSensor.h"

using namespace ev3api;
//E)

class PBPlaceDetectionCondition : public Condition
{
	//S)
	
	//E)

private:

	bool m_TF;

	bool m_Result_TF;

	int Red[3];

	int Yellow[3];

	int Blue[3];

	int Green[3];

	Calibration* m_pCalibration;

	ColorSensor* m_pColorSensor;

public:

	PBPlaceDetectionCondition(ColorSensor* pColorSensor, bool TF, Calibration* pCalibration);

	bool isSatisfy();

	void setDecisionBorder();

	~PBPlaceDetectionCondition();

	//S)
	int m_log[4];
	void log(int &loga, int &logb, int &logc);
	//E)
};

//S)

//E)

#endif	// CONDITION_PBPLACEDETECTIONCONDITION_H

//S)

//E)
