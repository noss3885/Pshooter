#include "Cellfield.h"
#include "DxLib.h"

using namespace std;

//�������̏���
Cellfield::Cellfield()
{
}

void Cellfield::set(char *data, int X, int Y) {
	m_XMAX = X, m_YMAX = Y;
	//X*Y�̏�����Ԃ̔z��𐶐�
	m_data = vector<vector<int> >(m_YMAX, vector<int>(m_XMAX, 0));
	for (int y = 0; y < m_YMAX; y++)
		for (int x = 0; x < m_XMAX; x++) {
			m_data[y][x] = data[x + y * m_XMAX] - '0';
		}
	//�摜��8*8�ɕ������ēǂݍ���
	LoadDivGraph("Image\\cell.png", 3, 3, 1, 8, 8, m_cellImg);
}

//�Z�������̐���֍X�V����֐�
void Cellfield::update() {
	vector<vector<int> > copy = m_data;
	for (int y = 0; y < m_YMAX; y++) {
		for (int x = 0; x < m_XMAX; x++) {
			int num3 = 0;  //����8�}�X�̐��̃Z��(3)�̌�
						   //���͂�T��
			for (int dy = -1; dy <= 1; dy++) {
				for (int dx = -1; dx <= 1; dx++) {
					int tx = x + dx, ty = y + dy;
					//�g�O�Ǝ������g�͐����Ȃ�
					if (tx < 0 || tx >= m_XMAX || ty < 0 || ty >= m_YMAX)continue;
					else if (dx == 0 && dy == 0)continue;
					//��(3)�Ȃ�Ή��Z
					else if (m_data[ty][tx] == 3)num3++;
				}
			}
			// 2/345/4
			//��(0)�����͂ɐ��̃Z����2����Ƃ����ɂȂ�
			//��(3)�����͂ɐ��̃Z����3~5����Ƃ������A����ȊO��2�Ɍ���
			//����ȊO(2,1)�͂��̂܂�1����
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
	//�X�V��Ԃ���
	m_data = copy;
}

//�Z����`�悷��֐�
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