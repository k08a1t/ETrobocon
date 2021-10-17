//S)
#include "TrainReader.h"

#include "../Device/SonarMeter.h"

using namespace ev3api;
//E)

TrainReader::TrainReader(SonarMeter* pSonarMeter)
//S)
: m_pSonarMeter(pSonarMeter)
//E)
{
	//S)
	m_train_situation=0;
	//E)
}

void TrainReader::readTrainSituation()
{
	//S)
		checkTrainDistance();
	//E)
}

int TrainReader::getTrainSituation()
{
	//S)
	return m_train_situation;
	//E)
}

void TrainReader::checkTrainDistance()
{
	//S)
	if(m_pSonarMeter->get()>=2&&m_pSonarMeter->get()<=42)
	{
		m_train_situation=1;
	}/*
	else if(m_pSonarMeter->get()>=60&&m_pSonarMeter->get()<=90)
	{
		m_train_situation=2;
	}*/
	else
	{
		m_train_situation=0;
	}
	//E)
}

TrainReader::~TrainReader()
{
	//S)
	
	//E)
}

//S)

//E)
