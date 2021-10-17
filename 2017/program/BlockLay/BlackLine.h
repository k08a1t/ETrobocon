// ˅

// ˄

#ifndef BLACKLINE_H_
#define BLACKLINE_H_

// ˅

class Angle;
class PolygonBlockPlace;

// ˄

class BlackLine
{
	// ˅
	
	// ˄

public:

	int m_Distance;

	int m_LineNumber;

private:

	PolygonBlockPlace* m_pConnectPBPlace[2];

public:

	BlackLine(int line_num);

	int getLineNumber();

	void setAdjoinDistance(bool blackblock);

	void setDistance(int distance);

	PolygonBlockPlace* getAnotherPBPlace(int PBPlaceNumber);

	int getDistance();

	~BlackLine();

	// ˅
public:
	
protected:
	
private:
	
	// ˄
};

// ˅

// ˄

#endif	// BLACKLINE_H_

// ˅

// ˄
