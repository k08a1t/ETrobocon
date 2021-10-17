// ˅
#include "RunArea.h"
#include "RunSection.h"


// ˄

RunArea::RunArea()
	// ˅
	:m_current_Section_index(0),m_Section_num(0)
	// ˄
{
	// ˅
	
	// ˄
}

bool RunArea::start()
{
	// ˅
	if (m_Section_list[m_current_Section_index]->start() == true) {	//区画が終了したら
		m_current_Section_index++;	//次の区画に移行
	}
	if (m_current_Section_index >= m_Section_num) {		//現在の区画番号が区画数以上になったら
		m_current_Section_index = 0;	//現在の区画番号をリセット
		return true;
	}
	else {
		return false;
	}

	// ˄
}

void RunArea::addSection(RunSection* pSection)
{
	// ˅
	m_Section_list[m_Section_num] = pSection;	//リストに区画を追加
	m_Section_num++;	//添字を＋１
	// ˄
}

RunArea::~RunArea()
{
	// ˅
	
	// ˄
}

// ˅

// ˄
