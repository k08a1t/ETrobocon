// ˅

// ˄

#ifndef RUNSECTION_H_
#define RUNSECTION_H_

// ˅
class Condition;
class DistanceMeter;
class Form;
class RunMethod;


// ˄

class RunSection
{
	// ˅
	
	// ˄

private:

	int m_section_number;

	Form* m_pForm;

	RunMethod* m_pRunMethod;

	Condition* m_pCondition;

	DistanceMeter* m_pDistanceMeter;

public:

	RunSection(int section_number, Condition* pCondition, RunMethod* pRunMethod, DistanceMeter pDistanceMeter, Form* pForm);

	bool start();

	~RunSection();

	// ˅
public:
	
protected:
	
private:
	RunSection(const RunSection&) = delete;
	RunSection& operator=(const RunSection&) = delete;
	
	// ˄
};

// ˅

// ˄

#endif	// RUNSECTION_H_

// ˅

// ˄
