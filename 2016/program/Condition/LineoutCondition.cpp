//S)
#include "LineoutCondition.h"

#include "Condition/LineCondition.h"
#include "Measure/Brightness.h"
//E)

LineoutCondition::LineoutCondition(int TargetCount,int BaseValue, Brightness* pBrightness)
//最初に白を0.4秒周期で連続で何回検知したら区画を終了するか(終了条件)を入力、次に何以上の数値が出たら白として処理するかを入力

//S)
:	m_TargetCount(TargetCount),
	m_BaseValue(BaseValue),
	m_pBrightness(pBrightness)
//E)
{
	//S)
	
	//E)
}

LineoutCondition::~LineoutCondition()
{
	//S)
	
	//E)
}

bool LineoutCondition::isSatisfy()
{
	//S)
 // for(int i=0;i=1;){
	if(m_BaseValue <= m_pBrightness->getBrightness()){//白を認識したらカウントに１を足す
		m_Count += 1;
	}
	else{
		m_Count = 0;//黒を認識したらカウントを０にする
		
	}
 	
	if(m_Count >= m_TargetCount){
		//i=1;
		 return true;//カウントが終了条件に達したら区画を終了する
	}
	else{
		return false;//カウントが終了条件に達していなかったら繰り返す
	}
//}
}
//E)

//S)

//E)
