// ˅

// ˄

#ifndef DISTANCECONDITION_H_
#define DISTANCECONDITION_H_

// ˅
#include "Condition.h"

class DistanceMeter;


// ˄

class DistanceCondition : public Condition
{
	// ˅
	
	// ˄

private:

	int m_target_distance;

	DistanceMeter* m_pDistanceMeter;

public:

	DistanceCondition(int t_distance, DistanceMeter pDistanceMeter);

	bool satisfy();

	~DistanceCondition();

	// ˅
public:
	
protected:
	
private:
	DistanceCondition(const DistanceCondition&) = delete;
	DistanceCondition& operator=(const DistanceCondition&) = delete;
	
	// ˄
};

// ˅

// ˄

#endif	// DISTANCECONDITION_H_

// ˅

// ˄
