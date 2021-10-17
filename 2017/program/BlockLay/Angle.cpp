// ˅
#include "Angle.h"

// ˄

Angle::Angle()
	// ˅
	
	// ˄
{
	// ˅
	/*0=1,30=2,-30=3,45=4,-45=5,60=6,-60=7,90=8,-90=9,105=10,-105=11,120=12,-120=13,135=14,-135=15,150=16,-150=17*/
	//-90=18,90=19

	m_AngleData[0][8] = 1;
	m_AngleData[0][18] = 8;
	m_AngleData[0][22] = 5;
	m_AngleData[1][15] = 6;
	m_AngleData[1][16] = 7;
	m_AngleData[1][19] = 1;
	m_AngleData[1][20] = 1;
	m_AngleData[2][3] = 7;
	m_AngleData[2][8] = 8;
	m_AngleData[2][9] = 1;
	m_AngleData[2][22] = 14;
	m_AngleData[2][24] = 16;
	m_AngleData[3][4] = 6;
	m_AngleData[3][8] = 3;
	m_AngleData[3][9] = 13;
	m_AngleData[3][24] = 17;
	m_AngleData[3][25] = 2;
	m_AngleData[4][3] = 7;
	m_AngleData[4][5] = 7;
	m_AngleData[4][10] = 12;
	m_AngleData[4][11] = 0;
	m_AngleData[4][24] = 3;
	m_AngleData[4][25] = 16;
	m_AngleData[5][4] = 7;
	m_AngleData[5][6] = 6;
	m_AngleData[5][10] = 1;
	m_AngleData[5][11] = 13;
	m_AngleData[5][25] = 17;
	m_AngleData[5][26] = 2;
	m_AngleData[6][5] = 7;
	m_AngleData[6][7] = 7;
	m_AngleData[6][12] = 12;
	m_AngleData[6][13] = 2;
	m_AngleData[6][25] = 3;
	m_AngleData[6][26] = 16;
	m_AngleData[7][6] = 6;
	m_AngleData[7][12] = 1;
	m_AngleData[7][13] = 9;
	m_AngleData[7][23] = 14;
	m_AngleData[7][26] = 17;
	m_AngleData[8][2] = 9;
	m_AngleData[8][3] = 2;
	m_AngleData[8][9] = 8;
	m_AngleData[8][18] = 9;
	m_AngleData[8][22] = 14;
	m_AngleData[9][2] = 1;
	m_AngleData[9][3] = 12;
	m_AngleData[9][8] = 9;
	m_AngleData[9][10] = 7;
	m_AngleData[9][14] = 8;
	m_AngleData[9][15] = 2;
	m_AngleData[10][4] = 13;
	m_AngleData[10][5] = 1;
	m_AngleData[10][9] = 6;
	m_AngleData[10][11] = 6;
	m_AngleData[10][14] = 3;
	m_AngleData[10][15] = 9;
	m_AngleData[11][4] = 1;
	m_AngleData[11][5] = 12;
	m_AngleData[11][10] = 7;
	m_AngleData[11][12] = 7;
	m_AngleData[11][16] = 8;
	m_AngleData[11][17] = 2;
	m_AngleData[12][6] = 13;
	m_AngleData[12][7] = 1;
	m_AngleData[12][11] = 6;
	m_AngleData[12][13] = 8;
	m_AngleData[12][16] = 3;
	m_AngleData[12][17] = 9;
	m_AngleData[13][6] = 3;
	m_AngleData[13][7] = 8;
	m_AngleData[13][12] = 9;
	m_AngleData[13][21] = 8;
	m_AngleData[13][23] = 15;
	m_AngleData[14][9] = 9;
	m_AngleData[14][10] = 2;
	m_AngleData[14][15] = 12;
	m_AngleData[14][18] = 8;
	m_AngleData[14][19] = 13;
	m_AngleData[15][1] = 7;
	m_AngleData[15][9] = 3;
	m_AngleData[15][10] = 8;
	m_AngleData[15][14] = 13;
	m_AngleData[15][19] = 12;
	m_AngleData[16][1] = 6;
	m_AngleData[16][11] = 9;
	m_AngleData[16][12] = 2;
	m_AngleData[16][17] = 12;
	m_AngleData[16][20] = 12;
	m_AngleData[17][11] = 3;
	m_AngleData[17][12] = 8;
	m_AngleData[17][16] = 13;
	m_AngleData[17][20] = 12;
	m_AngleData[17][21] = 9;
	m_AngleData[18][8] = 8;
	m_AngleData[18][14] = 9;
	m_AngleData[18][19] = 3;
	m_AngleData[18][22] = 4;
	m_AngleData[19][1] = 1;
	m_AngleData[19][14] = 12;
	m_AngleData[19][15] = 13;
	m_AngleData[19][18] = 2;
	m_AngleData[20][1] = 1;
	m_AngleData[20][16] = 12;
	m_AngleData[20][17] = 13;
	m_AngleData[20][21] = 3;
	m_AngleData[21][13] = 9;
	m_AngleData[21][17] = 8;
	m_AngleData[21][20] = 2;
	m_AngleData[21][23] = 5;
	m_AngleData[22][2] = 14;
	m_AngleData[22][8] = 14;
	m_AngleData[22][18] = 5;
	m_AngleData[22][24] = 10;
	m_AngleData[23][7] = 15;
	m_AngleData[23][13] = 14;
	m_AngleData[23][21] = 4;
	m_AngleData[23][26] = 10;
	m_AngleData[24][2] = 17;
	m_AngleData[24][3] = 16;
	m_AngleData[24][4] = 2;
	m_AngleData[24][22] = 11;
	m_AngleData[24][25] = 1;
	m_AngleData[25][3] = 3;
	m_AngleData[25][4] = 17;
	m_AngleData[25][5] = 16;
	m_AngleData[25][6] = 2;
	m_AngleData[25][24] = 1;
	m_AngleData[25][26] = 1;
	m_AngleData[26][5] = 3;
	m_AngleData[26][6] = 17;
	m_AngleData[26][7] = 16;
	m_AngleData[26][23] = 10;
	m_AngleData[26][25] = 1;

	// ˄
}

int Angle::getAngle(int Line1, int Line2)
{
	// ˅
	return m_AngleData[Line1][Line2];
	// ˄
}

Angle::~Angle()
{
	// ˅
	
	// ˄
}

// ˅

// ˄
