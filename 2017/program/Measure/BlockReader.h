//S)

//E)

#ifndef MEASURE_BLOCKREADER_H
#define MEASURE_BLOCKREADER_H

//S)
#include "ColorSensor.h"

using namespace ev3api;
//E)

class BlockReader
{
	//S)
	
	//E)

private:

	int m_Block_color;

	ColorSensor* m_pColorSensor;

public:

	BlockReader(ColorSensor* pColorSensor);

	void readBlockSituation();

	int getBlockSituation();

private:

	void checkBlockColor();

public:

	~BlockReader();

	//S)
	
	//E)
};

//S)

//E)

#endif	// MEASURE_BLOCKREADER_H

//S)

//E)
