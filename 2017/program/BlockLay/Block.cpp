// ˅
#include "Block.h"
#include "PolygonBlockPlace.h"
#include "Color.h"
// ˄

Block::Block(Color color)
	// ˅
	:m_Color(color)
	// ˄
{
	// ˅
	
	// ˄
}

void Block::setValidMovementComplete()
{
	// ˅
	m_ValidMovementCompleted = true;
	// ˄
}

void Block::setUseDiagram()
{
	// ˅
	m_UseDiagram = true;
	// ˄
}

bool Block::getValidMovementCompleted()
{
	// ˅
	return m_ValidMovementCompleted;
	// ˄
}

Color Block::getBlockColor()
{
	// ˅
	return m_Color;
	// ˄
}

bool Block::getUseDiagram()
{
	// ˅
	return m_UseDiagram;
	// ˄
}

Block::~Block()
{
	// ˅
	
	// ˄
}

// ˅

// ˄
