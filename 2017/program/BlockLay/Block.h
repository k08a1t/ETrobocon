// ˅

// ˄

#ifndef BLOCK_H_
#define BLOCK_H_

// ˅
#include "Color.h"
// ˄

class Block
{
	// ˅
	
	// ˄

public:

	Color m_Color;

	bool m_ValidMovementCompleted;

	bool m_UseDiagram;

	Block(Color color);

	void setValidMovementComplete();

	void setUseDiagram();

	bool getValidMovementCompleted();

	Color getBlockColor();

	bool getUseDiagram();

	~Block();

	// ˅
public:
	
protected:
	
private:
	
	// ˄
};

// ˅

// ˄

#endif	// BLOCK_H_

// ˅

// ˄
