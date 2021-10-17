//S)
#include "Field.h"

#include "BlockLined/Placegroup.h"
#include "BlockLined/Place.h"
#include "BlockLined/Color.h"

//E)

Field::Field(Place* pPresentPlace)
//S)
:m_PresentPoint(pPresentPlace),m_Place_listnum(0),m_Placegroup_listnum(0)
//E)
{
	//S)
	for(int i =0; i<5; i++){
		m_pPlacegroup[i] = nullptr;
	}
	for(int i =0; i<16; i++){
		m_pPlace[i] = nullptr;
	}
	//E)
}

void Field::MakeDistanceList(int StartPointNum, bool blockade)
{
	//S)
	
	//すべての置き場を100でリセット
	for (int i = 0; i<16; i++) {
		m_pPlace[i]->ResetDistance();
	}

	//blockadeが,偽の時はブロックすべてに-1(ブロック運搬時)
	for (int i = 0; i < 16; i++) {
		if (blockade == false) {
			if (m_pPlace[i]->getBlockExistence() == true) {
				m_pPlace[i]->setDistance(-1);
			}
		}
	}
	m_PresentPoint->setDistanceInit(100); //現在地を100にする

	m_pPlace[StartPointNum]->setDistanceInit(0);//起点ゼロリセット


	for(int x = 0; x < 10; x++) {
		for(int y = 0; y < 16; y++) {
			if(m_pPlace[y]->getDistance() > -1){
				m_pPlace[y]->setAdjoinDistance();
			}
		}
	}
	//E)
}

int Field::JudgementArrangementPoint(Color color)
{
	//S)
	
	//道のり一覧の作成
	int start = m_PresentPoint->getXcoord();
	MakeDistanceList(start, false);

	int num = 0;
	switch(color){
	case Red:
		num = 0;
		break;
	case Blue:
		num = 1;
		break;
	case Yellow:
		num = 2;
		break;
	case Green:
		num = 3;
		break;
	case Black:
		num = 4;
		break;
	}

	return m_pPlacegroup[num]->getNearestPlace();
	//E)
}

int Field::JudgementClosestBlock()
{
	//S)

	//道のり一覧の作成
	int start = m_PresentPoint->getXcoord();
	MakeDistanceList(start, true);

	//道のりから最も近いブロックの判定
	int BlockPlaceNumber = 0;
	int DisVal = 1000;
	int BlockNumber = 0;

	for (int i = 0; i<16; i++) {
		//ブロックの有無の判定
		if (m_pPlace[i]->getBlockExistence() == true) {
			if (DisVal >  m_pPlace[i]->getDistance() && m_pPlace[i]->getArrangeBlockExistence() == false) {
				BlockPlaceNumber = i;
				DisVal = m_pPlace[i]->getDistance();
				BlockNumber = m_pPlace[i]->getBlock();
		  }	
			else if(DisVal == m_pPlace[i]->getDistance()&& m_pPlace[i]->getArrangeBlockExistence() == false){
				if (BlockNumber > m_pPlace[i]->getBlock()) {
					BlockPlaceNumber = i;
					DisVal = m_pPlace[i]->getDistance();
					BlockNumber = m_pPlace[i]->getBlock();
				}
			}
	    }
	}

	return BlockPlaceNumber;

	//E)
}

void Field::DecisionPresentPoint(int NewPresentPoint)
{
	//S)
	m_PresentPoint = m_pPlace[NewPresentPoint];
	//E)
}

void Field::addPlace(Place* pPlace)
{
	//S)
	m_pPlace[m_Place_listnum] = pPlace;
	m_Place_listnum++;
	//E)
}

void Field::addPlacegroup(Placegroup* pPlacegroup)
{
	//S)
	//1赤、2青、３黄色、４緑、５出口　　appで設定しました
	m_pPlacegroup[m_Placegroup_listnum] = pPlacegroup;
	m_Placegroup_listnum++;
	//E)
}

Place* Field::getPresentPoint()
{
	//S)
	return m_PresentPoint;
	//E)
}

Field::~Field()
{
	//S)
	
	//E)
}

//S)
void  Field::log(int &loga, int &logb, int &logc, int &logd, int &loge, int &logf, int &logg, int &logh, int &logi, int &logj, int &logk, int &logl, int &logm, int &logn, int &logo, int &logp)
{
	loga = m_PresentPoint->getXcoord();//m_pPlace[0]->getDistance();
	logb = m_pPlace[1]->getDistance();
	logc = m_pPlace[2]->getDistance();
	logd = m_pPlace[3]->getDistance();
	loge = m_pPlace[4]->getDistance();
	logf = m_pPlace[5]->getDistance();
	logg = m_pPlace[6]->getDistance();
	logh = m_pPlace[7]->getDistance();
	logi = m_pPlace[8]->getDistance();
	logj = m_pPlace[9]->getDistance();
	logk = m_pPlace[10]->getDistance();
	logl = m_pPlace[11]->getDistance();
	logm = m_pPlace[12]->getDistance();
	logn = m_pPlace[13]->getDistance();
	logo = m_pPlace[14]->getDistance();
	logp = m_pPlace[15]->getDistance();
}
//E)
