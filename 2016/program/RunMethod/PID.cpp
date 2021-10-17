//S)
#include "PID.h"

//E)

PID::PID(float p_value, float i_value, float d_value)
//S)
:	m_P_coefficient(p_value),
	m_I_coefficient(i_value),
	m_D_coefficient(d_value),
	m_d_now(0),
	m_d_pre(0),
	m_num(0)
//E)
{
	//S)
	
	//E)
}

int PID::calcControllValue(int now_value)
{
	//S)
	float d_control = 0;
	float p_control = 0;
	float i_control = 0;
	int   pid_total = 0;

	/*P����v�Z*/
	p_control = now_value * m_P_coefficient;

	/*D����v�Z*/
	m_d_pre = m_d_now;
	m_d_now = now_value;
	d_control = (m_d_now - m_d_pre) * m_D_coefficient;

	/*I����v�Z*/
	if(now_value * m_num ==0){
		m_num = 0;
	}
	
	if(now_value>0){
		m_num ++;
	}
	else if(now_value<0){
		m_num --;
	}
	
	i_control = m_num * m_I_coefficient;

	/*PID�Z�o�l*/
	pid_total = static_cast<int>(p_control + i_control + d_control);

	return pid_total;
	//E)
}

PID::~PID()
{
	//S)
	
	//E)
}

//S)

//E)
