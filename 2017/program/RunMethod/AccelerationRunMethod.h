//S)

//E)

#ifndef RUNMETHOD_ACCELERATIONRUNMETHOD_H
#define RUNMETHOD_ACCELERATIONRUNMETHOD_H

//S)

//E)

class AccelerationRunMethod : public RunMethod
{
	//S)
	
	//E)

private:

	int m_accelerate_num;

	int m_max_speed;

	Motor* m_pLeftMotor;

	Motor* m_pRightMotor;

public:

	AccelerationRunMethod(int max_speed, Motor* pLeftMotor, Motor* pRightMotor, Fork* pFork);

	void run();

	~AccelerationRunMethod();

	//S)
	
	//E)
};

//S)

//E)

#endif	// RUNMETHOD_ACCELERATIONRUNMETHOD_H

//S)

//E)
