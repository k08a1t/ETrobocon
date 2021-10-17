//S)
#include "DynamicRunArea.h"

#include "RouteGuide/RunArea.h"

using namespace ev3api;
//E)

bool DynamicRunArea::start()
{
	//S)
	if (m_pRunBlock_list[m_current_index]->start() == true){
		m_current_index++;
		
		if(m_list_num > m_current_index){

			while (judgeRunBlock() == false){
				
				m_current_index++;
				
				if (m_list_num <= m_current_index){
					break;
				}
		
			}
		}
	}

	if (m_list_num <= m_current_index){
		m_current_index = 0;
		return true;
	}
	else{
		return false;
	}
	//E)
}

void DynamicRunArea::setBranchNumber(int branch_num)
{
	//S)
	int value = branch_num;
	m_branch_number[0] = (value % 100); value /= 100;//  2桁目と1桁目を取り出す
	m_branch_number[1] = (value % 100); value /= 100;//  4桁目と3桁目を取り出す
	m_branch_number[2] = (value % 100); value /= 100;//  6桁目と5桁目を取り出す
	m_branch_number[3] = (value % 100); value /= 100;//  8桁目と7桁目を取り出す

	//E)
}

bool DynamicRunArea::judgeRunBlock()
{
	//S)
	int num = m_pRunBlock_list[m_current_index]->getBlockNumber();

	if		(num == m_branch_number[0])	{return true;}
	else if (num == m_branch_number[1])	{return true;}
	else if (num == m_branch_number[2])	{return true;}
	else if (num == m_branch_number[3])	{return true;}
	else if (num == 0)					{return true;}
	else{
		return false;
	}
	//E)
}

DynamicRunArea::DynamicRunArea()
//S)
 : RunArea()
//E)
{
	//S)
	m_branch_number[0] = 0;
	m_branch_number[1] = 0;
	m_branch_number[2] = 0;
	m_branch_number[3] = 0;
	//E)
}

DynamicRunArea::~DynamicRunArea()
{
	//S)
	
	//E)
}

//S)

//E)
