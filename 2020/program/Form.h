// ˅

// ˄

#ifndef FORM_H_
#define FORM_H_

// ˅
class Clock;
class Motor;


// ˄

class Form
{
	// ˅
	
	// ˄

private:

	int m_arm_position;

	Motor* m_pArmMotor;

	Clock* m_pClock;

public:

	Form(int arm_position, Motor* pArmMotor, Clock* pClock);

	void changeForm();

	~Form();

	// ˅
public:
	
protected:
	
private:
	Form(const Form&) = delete;
	Form& operator=(const Form&) = delete;
	
	// ˄
};

// ˅

// ˄

#endif	// FORM_H_

// ˅

// ˄
