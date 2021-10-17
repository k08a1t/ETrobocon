// ˅
#include "DistanceCondition.h"
#include "DistanceMeter.h"


// ˄

DistanceCondition::DistanceCondition(int t_distance, DistanceMeter pDistanceMeter)
	// ˅
	:m_target_distance(t_distance),m_pDistanceMeter(pDistanceMeter)
	// ˄
{
	// ˅
	
	// ˄
}

bool DistanceCondition::satisfy()
{
	// ˅
	int distance;
	distance = m_pDistanceMeter->getSectionDistance();
	if (distance >= 0) {
		if (distance >= m_target_distance) {
			return true;
		}
		else {
			return false;
		}
	}
	else {
		if (distance <= m_target_distance) {
			return true;
		}
		else {
			return false;
		}
	}
	// ˄
}

DistanceCondition::~DistanceCondition()
{
	// ˅
	
	// ˄
}

// ˅

// ˄
