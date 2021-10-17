//S)

//E)

#ifndef MEASURE_TRAINREADER_H
#define MEASURE_TRAINREADER_H

//S)
#include "Device/SonarMeter.h"
 
using namespace ev3api;
//E)

class TrainReader
{
	//S)
	
	//E)

private:

	int m_train_situation;

	SonarMeter* m_pSonarMeter;

public:

	TrainReader(SonarMeter* pSonarMeter);

	void readTrainSituation();

	int getTrainSituation();

private:

	void checkTrainDistance();

public:

	~TrainReader();

	//S)
	
	//E)
};

//S)

//E)

#endif	// MEASURE_TRAINREADER_H

//S)

//E)
