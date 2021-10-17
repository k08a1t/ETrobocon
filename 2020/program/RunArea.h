// ˅

// ˄

#ifndef RUNAREA_H_
#define RUNAREA_H_

// ˅
#include <vector>

class RunSection;

using namespace std;


// ˄

class RunArea
{
	// ˅
	
	// ˄

private:

	int m_current_Section_index;

	RunSection* m_Section_list[30];

	int m_Section_num;

	RunSection* m_pRunSection;

public:

	RunArea();

	bool start();

	void addSection(RunSection* pSection);

	~RunArea();

	// ˅
public:
	
protected:
	
private:
	RunArea(const RunArea&) = delete;
	RunArea& operator=(const RunArea&) = delete;
	
	// ˄
};

// ˅

// ˄

#endif	// RUNAREA_H_

// ˅

// ˄
