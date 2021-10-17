//S)
#include "Solution.h"

#include "BlockLined/Route.h"
#include "BlockLined/Block.h"
#include "BlockLined/MovementType.h"


//E)

Solution::Solution(Route* pRoute, Block* pBlockA, Block* pBlockB, Block* pBlockC, Block* pBlockD)
//S)
:m_RouteSituation(-3),m_PurposeBlock(pBlockB),m_AmountMovement(0),m_couse_num(0),m_transport_count(0),m_pRoute(pRoute)
//E)  //決め打ちのブロックが黒だった場合「m_RouteSituation」の値を-1に変更する  普段は-3
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
	//m_AmountMovement = m_pRoute->tranportSearchRoute();//エラーチェック用

	//m_RouteSituationは1がブロックに向かう格子走行、2がブロックを見る、3はブロックを運ぶ格子走行、4はブロックを置く、5は出口に向かう格子走行
	//決め打ち追加　-3がブロックに向かう格子走行、-2がブロックを置く、-1がブロックを置く格子走行
	if(m_RouteSituation == -3){
		m_couse_num++;
		if(m_couse_num < 2){//格子繰り返し判定******ブロック配置終了までの移動量入力	
		}
		else{
			m_RouteSituation = -2;
		}
	}
	else if(m_RouteSituation == -2){
			m_pBlock[0]->setArrangementComplete();//Aブロックを配置済みにする
			m_RouteSituation = -1;
	}
	else if(m_RouteSituation == -1){
		m_couse_num++;
		if(m_couse_num < 3){//格子繰り返し判定*********決め打ちの合計移動量入力	
		}
		else{
			//m_pBlock[0]->setArrangementComplete();//Aブロックを配置済みにする //決め打ちのブロックが黒だった場合に使用
			m_couse_num = 0;
			m_RouteSituation = 2;
		}
	}

	else if(m_RouteSituation == 0){
		m_AmountMovement = m_pRoute->obtainSearchRoute();//ブロックに向かうコースを作成させ移動量を受け取る
		int blocknum = m_pRoute->getTransportBlock();//対象のブロックの番号を取得
		m_PurposeBlock = m_pBlock[blocknum];//対象のブロックをメンバに設定
		m_RouteSituation = 1;
	}
	else if(m_RouteSituation == 1){
		m_couse_num++;
		if(m_couse_num < m_AmountMovement){//格子繰り返し判定	
		}
		else{
			m_couse_num = 0;
			m_RouteSituation = 2;
		}
	}
	else if(m_RouteSituation == 2){

		if(m_PurposeBlock->getMovementAdvisability() == MovementProhibition){//移動禁止ブロック（黒）だったら4に飛ぶ
			m_couse_num = 0;
			m_RouteSituation = 4;
		}else{
			m_AmountMovement = m_pRoute->tranportSearchRoute();//ブロックを置くコースを作成させ移動量を受け取る
			m_RouteSituation = 3;
		}
	}
	else if(m_RouteSituation == 3){
		m_couse_num++;
		if(m_couse_num < m_AmountMovement){//格子繰り返し判定	
		}
		else{
			m_couse_num = 0;
			m_transport_count++;//ブロックを運んだ回数をカウントする
			m_RouteSituation = 4;
		}
	}
	else if(m_RouteSituation == 4){
		m_PurposeBlock->setArrangementComplete();//ブロックを配置済みにする
		//m_pRoute->SettingBlockRoute();//ブロック置いて後ろを向いた状態に設定する。置き場と向きの設定

		if(checkFinished() == false){//ブロックがすべて並べ終わったら5、まだなら１に戻る
			m_RouteSituation = 1;
			m_AmountMovement = m_pRoute->obtainSearchRoute();//ブロックに向かうコースを作成させ移動量を受け取る
			int blocknum2 = m_pRoute->getTransportBlock();//対象のブロックの番号を取得
			m_PurposeBlock = m_pBlock[blocknum2];//対象のブロックをメンバに設定
		}
		else{
			m_AmountMovement = m_pRoute->escapeSearchRoute();//出口に向かう（ブロックを置くコース）を作成させ移動量を受け取る
			m_RouteSituation = 5;
		}
	}
	else{
		m_couse_num++;
		if(m_couse_num < m_AmountMovement){//格子繰り返し判定
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
	if(m_transport_count == 2){  //決め打ちのブロックが黒の場合３に変える 普段は２
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
