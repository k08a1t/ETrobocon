//S)
#include "BlockLineRunArea.h"

#include "RouteGuide/RunArea.h"
#include "BlockLined/Solution.h"

using namespace ev3api;
//E)

BlockLineRunArea::BlockLineRunArea(RunArea* pCross, RunArea* pSetting, RunArea* plook, Solution* pSolution)
//S)
	: RunArea(), m_list_num(0), m_finish(false), m_first(false),  m_pSolution(pSolution)
//E)
{
	//S)
	m_pBLRunArea[0] = pCross; 
	m_pBLRunArea[1] = pSetting; 
	m_pBLRunArea[2] = plook;
	//E)
}

bool BlockLineRunArea::start()
{
	//S)
	//���߂�1�񂾂��u��@�N���X�v���Ăяo���B
	if(m_first == true){
		judgeBLArea();
		m_first = false;
	}

	if(m_pBLRunArea[m_list_num]->start() == true){
		judgeBLArea();//�G���A���I�������Ƃ��Ɂu��@�N���X�v���Ăяo���B
	}

	if (m_finish == true){
		return true;
	}
	else {
		return false;
	}
	//E)
}

void BlockLineRunArea::judgeBLArea()
{
	//S)
	int solu = m_pSolution->makeSolution();

	if(solu == 1 || solu == 3 || solu == 5 ||solu == -3 || solu == -1){
		m_list_num = 0;//�i�q���s
	}
	else if(solu == 2){
		m_list_num = 2;//�u���b�N�̐F������
	}
	else if(solu == 4 || solu == -2){
		m_list_num = 1;//�u���b�N��u��
	}
	else{
		m_finish = true;
	}
	//E)
}

BlockLineRunArea::~BlockLineRunArea()
{
	//S)
	
	//E)
}

//S)

//E)
