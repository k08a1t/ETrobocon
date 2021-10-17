//S)

//E)

#ifndef RUNMETHOD_PID_H
#define RUNMETHOD_PID_H

//S)

//E)

class PID
{
	//S)
	
	//E)

private:

	float m_P_coefficient;

	float m_I_coefficient;

	float m_D_coefficient;

	int m_history;

	int m_d_now;

	int m_d_pre;

	int m_i_list[13];

	int m_num;

public:

	PID(float p_value, float i_value, float d_value);

	int calcControllValue(int now_value);

	~PID();

	//S)
	
	//E)
};

//S)

//E)

#endif	// RUNMETHOD_PID_H

//S)

//E)
