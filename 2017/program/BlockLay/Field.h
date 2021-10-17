// ˅

// ˄

#ifndef FIELD_H_
#define FIELD_H_

// ˅
class BlackLine;
class Block;
class BlockPlace;
class Shape;
class PolygonBlockPlace;
// ˄

class Field
{
	// ˅
	
	// ˄

private:

	int m_PresentPoint;

	int m_EPcode;

	bool m_CreatePentagon;

	Block* m_pBlock[5];

	Shape* m_pShape[14];

	BlackLine* m_pBlackLine[27];

	PolygonBlockPlace* m_pPBPlace[15];

public:

	Field(int pPresentPoint, Block* pRedBlock, Block* pYellowBlock, Block* pBlueBlock, Block* pGreenBlock, Block* pBlackBlock);

	void convertEPcode(int epcode);

	int getPresentPoint();

	void makeDistanceList(int StartPlaceNumber, bool blackblock);

	void makeDistancefromSCBList();

	int JudgementClosestBlock();

	void renewalPresentPoint(int NewPresentPoint);

	void decideDiagram();

	~Field();

	// ˅
public:
	
protected:
	
private:
	
	// ˄
};

// ˅

// ˄

#endif	// FIELD_H_

// ˅

// ˄
