// ˅

// ˄

#ifndef BLOCKPLACE_H_
#define BLOCKPLACE_H_

// ˅
class Block;

// ˄

class BlockPlace
{
	// ˅
	
	// ˄

protected:

	int m_PlaceNumber;

	int m_Distance;

	Block* m_ArrangementPlan;

	int m_DistanceData[16];

public:

	BlockPlace(int PlaceNumber, int distance0, int distance1, int distance2, int distance3, int distance4, int distance5, int distance6, int distance7, int distance8, int distance9, int distance10, int distance11, int distance12, int distance13, int distance14, int distance15);

	void setArrangementPlan(Block* block);

	int getDistance();

	int getPlaceNumber();

	Block* getArrangementPlan();

	int getDistanceData(int AnotherPlaceNumber);

	~BlockPlace();

	// ˅
public:
	
protected:
	
private:
	
	// ˄
};

// ˅

// ˄

#endif	// BLOCKPLACE_H_

// ˅

// ˄
