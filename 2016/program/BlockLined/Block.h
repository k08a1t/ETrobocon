//S)

//E)

#ifndef BLOCKLINED_BLOCK_H
#define BLOCKLINED_BLOCK_H

//S)
#include "BlockLined/ColorDistinguish.h"
#include "BlockLined/MovementType.h"
#include "BlockLined/Color.h"

//using namespace ev3api;
//E)

class Block
{
	//S)
	
	//E)

private:

	Color m_Color;

	bool m_Arrangement;

	MovementType m_MovementAdvisability;

	int m_Number;

	ColorDistinguish* m_pColorDistinguish;

public:

	Block(Color t_Color, ColorDistinguish* pColorDistinguish, int number);

	void SearchColor();

	Color ObtainmentColor();

	void setArrangementComplete();

	bool getArrangement();

	MovementType getMovementAdvisability();

	int getBlockNumber();

	~Block();

	void LCDcolorout();

	//S)
	
	//E)
};

//S)

//E)

#endif	// BLOCKLINED_BLOCK_H

//S)

//E)
