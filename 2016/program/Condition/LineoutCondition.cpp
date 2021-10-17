//S)
#include "LineoutCondition.h"

#include "Condition/LineCondition.h"
#include "Measure/Brightness.h"
//E)

LineoutCondition::LineoutCondition(int TargetCount,int BaseValue, Brightness* pBrightness)
//�ŏ��ɔ���0.4�b�����ŘA���ŉ��񌟒m����������I�����邩(�I������)����́A���ɉ��ȏ�̐��l���o���甒�Ƃ��ď������邩�����

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
	if(m_BaseValue <= m_pBrightness->getBrightness()){//����F��������J�E���g�ɂP�𑫂�
		m_Count += 1;
	}
	else{
		m_Count = 0;//����F��������J�E���g���O�ɂ���
		
	}
 	
	if(m_Count >= m_TargetCount){
		//i=1;
		 return true;//�J�E���g���I�������ɒB����������I������
	}
	else{
		return false;//�J�E���g���I�������ɒB���Ă��Ȃ�������J��Ԃ�
	}
//}
}
//E)

//S)

//E)
