// ˅

// ˄

#ifndef RUNCOURSE_H_
#define RUNCOURSE_H_

// ˅
#include <vector>

class RunArea;

using namespace std;


// ˄

class RunCourse
{
	// ˅
	
	// ˄

private:

	int m_current_Area_index;

	RunArea* m_Area_list[10];

	int m_Area_num;

	RunArea* m_pRunArea;

public:

	RunCourse();

	bool startRun();

	void addRunArea(RunArea* pArea);

	~RunCourse();

	// ˅
public:
	
protected:
	
private:
	RunCourse(const RunCourse&) = delete;
	RunCourse& operator=(const RunCourse&) = delete;
	
	// ˄
};

// ˅

// ˄

#endif	// RUNCOURSE_H_

// ˅

// ˄
