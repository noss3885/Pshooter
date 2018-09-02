#include "Cellfield.h"
#include "DxLib.h"

using namespace std;

//初期化の処理
Cellfield::Cellfield()
{
}

void Cellfield::set(char *data, int X, int Y) {
	m_XMAX = X, m_YMAX = Y;
	//X*Yの初期状態の配列を生成
	m_data = vector<vector<int> >(m_YMAX, vector<int>(m_XMAX, 0));
	for (int y = 0; y < m_YMAX; y++)
		for (int x = 0; x < m_XMAX; x++) {
			m_data[y][x] = data[x + y * m_XMAX] - '0';
		}
	//画像を8*8に分割して読み込む
	LoadDivGraph("Image\\cell.png", 3, 3, 1, 8, 8, m_cellImg);
}

//セルを次の世代へ更新する関数
void Cellfield::update() {
	vector<vector<int> > copy = m_data;
	for (int y = 0; y < m_YMAX; y++) {
		for (int x = 0; x < m_XMAX; x++) {
			int num3 = 0;  //周囲8マスの生のセル(3)の個数
						   //周囲を探索
			for (int dy = -1; dy <= 1; dy++) {
				for (int dx = -1; dx <= 1; dx++) {
					int tx = x + dx, ty = y + dy;
					//枠外と自分自身は数えない
					if (tx < 0 || tx >= m_XMAX || ty < 0 || ty >= m_YMAX)continue;
					else if (dx == 0 && dy == 0)continue;
					//生(3)ならば加算
					else if (m_data[ty][tx] == 3)num3++;
				}
			}
			// 2/345/4
			//死(0)かつ周囲に生のセルが2個あるとき生になる
			//生(3)かつ周囲に生のセルが3~5個あるとき生存、それ以外は2に減る
			//それ以外(2,1)はそのまま1減る
			if (m_data[y][x] == 0) {
				if (num3 == 2)
					copy[y][x] = 3;
			}
			else if (m_data[y][x] == 3) {
				if (num3 < 3 || num3 > 5)
					copy[y][x] = 2;
			}
			else
				copy[y][x]--;
		}
	}
	//更新状態を代入
	m_data = copy;
}

//セルを描画する関数
void Cellfield::draw() {
	for (int y = 0; y < m_YMAX; y++) {
		for (int x = 0; x < m_XMAX; x++) {
			if (m_data[y][x] > 0) {
				DrawGraph(x * 8, y * 8, m_cellImg[m_data[y][x] - 1], TRUE);
			}
		}
	}
}

void Cellfield::reset(char *data) {
	m_data = vector<vector<int> >(m_YMAX, vector<int>(m_XMAX, 0));
	for (int y = 0; y < m_YMAX; y++)
		for (int x = 0; x < m_XMAX; x++) {
			m_data[y][x] = data[x + y * m_XMAX] - '0';
		}
}

void Cellfield::shot(int sx, int sy, int dir) {
	switch (dir) {
	case 0:  //UP
		if (sx >= 0 && sx + 2 < m_XMAX && sy >= 1 && sy + 1 < m_YMAX) {
			m_data[sy][sx + 1] = 3;
			m_data[sy][sx + 2] = 3;
			m_data[sy + 1][sx + 1] = 2;
			m_data[sy + 1][sx + 2] = 2;
		}
		break;
	case 1:  //RIGHT
		if (sx >= 0 && sx + 4 < m_XMAX && sy >= 0 && sy + 2 < m_YMAX) {
			m_data[sy + 1][sx + 3] = 3;
			m_data[sy + 2][sx + 3] = 3;
			m_data[sy + 1][sx + 2] = 2;
			m_data[sy + 2][sx + 2] = 2;
		}
		break;
	case 2:  //DOWN
		if (sx >= 0 && sx + 2 < m_XMAX && sy >= 0 && sy + 4 < m_YMAX) {
			m_data[sy + 3][sx + 1] = 3;
			m_data[sy + 3][sx + 2] = 3;
			m_data[sy + 2][sx + 1] = 2;
			m_data[sy + 2][sx + 2] = 2;
		}
		break;
	case 3:  //LEFT
		if (sx >= 1 && sx + 1 < m_XMAX && sy >= 0 && sy + 2 < m_YMAX) {
			m_data[sy + 1][sx] = 3;
			m_data[sy + 2][sx] = 3;
			m_data[sy + 1][sx + 1] = 2;
			m_data[sy + 2][sx + 1] = 2;
		}
		break;
	default:
		break;
	}
}

int Cellfield::damage(int px, int py) {
	int dmg = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (px + j < 0 || px + j >= m_XMAX || py + i < 0 || py + i >= m_YMAX)continue;
			if (m_data[py + i][px + j] == 3)dmg++;
		}
	}
	return dmg;
}