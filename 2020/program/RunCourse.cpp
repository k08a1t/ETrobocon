// ˅
#include "RunArea.h"
#include "RunCourse.h"


// ˄

RunCourse::RunCourse()
	// ˅
	:m_current_Area_index(0),m_Area_num(0)
	// ˄
{
	// ˅
	
	// ˄
}

bool RunCourse::startRun()
{
	// ˅
	if (m_Area_list[m_current_Area_index]->start() == true) {	//エリア内の区画がすべて終了したら
		m_current_Area_index++;		//次のエリアに移行
	}
	if (m_current_Area_index >= m_Area_num) {	//現在エリアの番号がエリア数以上になったら
		m_current_Area_index = 0;	//現在のエリア番号をリセット
		return true;
	}
	else {
		return false;
	}
	
	// ˄
}

void RunCourse::addRunArea(RunArea* pArea)
{
	// ˅
	m_Area_list[m_Area_num] = pArea;	//リスト(配列)にエリアを追加
	m_Area_list++;	//添字を＋１
	// ˄
}

RunCourse::~RunCourse()
{
	// ˅
	
	// ˄
}

// ˅

// ˄
