//S)
#include "RunArea.h"

#include "RouteGuide/Runblock.h"

using namespace ev3api;
//E)

bool RunArea::start()
{
	//S)
	if (m_pRunBlock_list[m_current_index] -> start() == true){
		m_current_index++;
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

void RunArea::addBlock(RunBlock* pBlock)
{
	//S)
	m_pRunBlock_list[m_list_num] = pBlock;
	m_list_num++;
	//E)
}

RunArea::RunArea()
//S)
	:m_list_num(0),m_current_index(0)
//E)
{
	//S)
	
	//E)
}

RunArea::~RunArea()
{
	//S)
	
	//E)
}

//S)

//E)
