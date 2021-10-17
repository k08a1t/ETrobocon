//S)
#include "Solution.h"

#include "BlockLined/Route.h"
#include "BlockLined/Block.h"
#include "BlockLined/MovementType.h"


//E)

Solution::Solution(Route* pRoute, Block* pBlockA, Block* pBlockB, Block* pBlockC, Block* pBlockD)
//S)
:m_RouteSituation(-3),m_PurposeBlock(pBlockB),m_AmountMovement(0),m_couse_num(0),m_transport_count(0),m_pRoute(pRoute)
//E)  //���ߑł��̃u���b�N�����������ꍇ�um_RouteSituation�v�̒l��-1�ɕύX����  ���i��-3
{
	//S)
	m_pBlock[0] = pBlockA; 
	m_pBlock[1] = pBlockB;
	m_pBlock[2] = pBlockC;
	m_pBlock[3] = pBlockD;
	//E)
}

int Solution::makeSolution()
{
	//S)
	//m_AmountMovement = m_pRoute->tranportSearchRoute();//�G���[�`�F�b�N�p

	//m_RouteSituation��1���u���b�N�Ɍ������i�q���s�A2���u���b�N������A3�̓u���b�N���^�Ԋi�q���s�A4�̓u���b�N��u���A5�͏o���Ɍ������i�q���s
	//���ߑł��ǉ��@-3���u���b�N�Ɍ������i�q���s�A-2���u���b�N��u���A-1���u���b�N��u���i�q���s
	if(m_RouteSituation == -3){
		m_couse_num++;
		if(m_couse_num < 2){//�i�q�J��Ԃ�����******�u���b�N�z�u�I���܂ł̈ړ��ʓ���	
		}
		else{
			m_RouteSituation = -2;
		}
	}
	else if(m_RouteSituation == -2){
			m_pBlock[0]->setArrangementComplete();//A�u���b�N��z�u�ς݂ɂ���
			m_RouteSituation = -1;
	}
	else if(m_RouteSituation == -1){
		m_couse_num++;
		if(m_couse_num < 3){//�i�q�J��Ԃ�����*********���ߑł��̍��v�ړ��ʓ���	
		}
		else{
			//m_pBlock[0]->setArrangementComplete();//A�u���b�N��z�u�ς݂ɂ��� //���ߑł��̃u���b�N�����������ꍇ�Ɏg�p
			m_couse_num = 0;
			m_RouteSituation = 2;
		}
	}

	else if(m_RouteSituation == 0){
		m_AmountMovement = m_pRoute->obtainSearchRoute();//�u���b�N�Ɍ������R�[�X���쐬�����ړ��ʂ��󂯎��
		int blocknum = m_pRoute->getTransportBlock();//�Ώۂ̃u���b�N�̔ԍ����擾
		m_PurposeBlock = m_pBlock[blocknum];//�Ώۂ̃u���b�N�������o�ɐݒ�
		m_RouteSituation = 1;
	}
	else if(m_RouteSituation == 1){
		m_couse_num++;
		if(m_couse_num < m_AmountMovement){//�i�q�J��Ԃ�����	
		}
		else{
			m_couse_num = 0;
			m_RouteSituation = 2;
		}
	}
	else if(m_RouteSituation == 2){

		if(m_PurposeBlock->getMovementAdvisability() == MovementProhibition){//�ړ��֎~�u���b�N�i���j��������4�ɔ��
			m_couse_num = 0;
			m_RouteSituation = 4;
		}else{
			m_AmountMovement = m_pRoute->tranportSearchRoute();//�u���b�N��u���R�[�X���쐬�����ړ��ʂ��󂯎��
			m_RouteSituation = 3;
		}
	}
	else if(m_RouteSituation == 3){
		m_couse_num++;
		if(m_couse_num < m_AmountMovement){//�i�q�J��Ԃ�����	
		}
		else{
			m_couse_num = 0;
			m_transport_count++;//�u���b�N���^�񂾉񐔂��J�E���g����
			m_RouteSituation = 4;
		}
	}
	else if(m_RouteSituation == 4){
		m_PurposeBlock->setArrangementComplete();//�u���b�N��z�u�ς݂ɂ���
		//m_pRoute->SettingBlockRoute();//�u���b�N�u���Č�����������Ԃɐݒ肷��B�u����ƌ����̐ݒ�

		if(checkFinished() == false){//�u���b�N�����ׂĕ��׏I�������5�A�܂��Ȃ�P�ɖ߂�
			m_RouteSituation = 1;
			m_AmountMovement = m_pRoute->obtainSearchRoute();//�u���b�N�Ɍ������R�[�X���쐬�����ړ��ʂ��󂯎��
			int blocknum2 = m_pRoute->getTransportBlock();//�Ώۂ̃u���b�N�̔ԍ����擾
			m_PurposeBlock = m_pBlock[blocknum2];//�Ώۂ̃u���b�N�������o�ɐݒ�
		}
		else{
			m_AmountMovement = m_pRoute->escapeSearchRoute();//�o���Ɍ������i�u���b�N��u���R�[�X�j���쐬�����ړ��ʂ��󂯎��
			m_RouteSituation = 5;
		}
	}
	else{
		m_couse_num++;
		if(m_couse_num < m_AmountMovement){//�i�q�J��Ԃ�����
		}
		else{
			m_couse_num = 0;
			m_RouteSituation = 6;
		}

	}

	return m_RouteSituation;

	//E)
}

bool Solution::checkFinished()
{
	//S)
	if(m_transport_count == 2){  //���ߑł��̃u���b�N�����̏ꍇ�R�ɕς��� ���i�͂Q
		return true;
	}
	else{
		if(m_pBlock[0]->getArrangement() == false){
			return false;
		}
		else if(m_pBlock[1]->getArrangement() == false){
			return false;
		}
		else if(m_pBlock[2]->getArrangement() == false){
			return false;
		}
		else if(m_pBlock[3]->getArrangement() == false){
			return false;
		}
		else{
			return true;
		}
	}
	//E)
}

void Solution::searchBlockcolor()
{
	//S)
	m_PurposeBlock->SearchColor();
	//E)
}

int Solution::getCourse()
{
	//S)
	int value = m_pRoute->getTravelDirection(m_couse_num);
	return value;
	//E)
}

int Solution::getEscapeDirecrion()
{
	//S)
	int RunbodyDirection = m_pRoute->getRunbodyDirection();

	return RunbodyDirection;
	//E)
}

Solution::~Solution()
{
	//S)
	
	//E)
}

void Solution::LCDout()
{
	//S)
	m_PurposeBlock->LCDcolorout();
	//E)
}

//S)

//E)
