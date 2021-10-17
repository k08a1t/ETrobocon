// ˅

// ˄

#ifndef ROUTE_H_
#define ROUTE_H_

// ˅

class Block;
class Field;
class PolygonBlockPlace;
// ˄

class Route
{
	// ˅

	// ˄

private:

	PolygonBlockPlace* m_ViaPoint[20];

	int m_ViaNod;

	int m_Process[20];

protected:

	Field* m_pField;

private:

	Block* m_pTransportBlock;

	PolygonBlockPlace* m_pThroughPBPlace[17];

public:

	Route(Field* pField);

	int ObtainSearchRoute();

	Block* getTransportBlock();

	int getProsess(int num);

	int TransportSearchRoute();

	int EscapeSearchRoute();

	void setProsess(int num, int acceed);

	~Route();

	// ˅
public:
	
protected:
	
private:
	
	// ˄
};

// ˅

// ˄

#endif	// ROUTE_H_

// ˅

// ˄
