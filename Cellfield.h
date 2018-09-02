#pragma once

#include<vector>

class Cellfield
{
public:
	Cellfield();
	void set(char *data, int X, int Y);
	void update();
	void draw();
	void reset(char *data);
	void shot(int sx, int sy, int dir);
	int damage(int px, int py);

private:
	std::vector<std::vector<int> > m_data;  //�Z���̏�̏���ۑ�
	int m_XMAX, m_YMAX;    //�Z���̏�̕��ƍ���
	int m_cellImg[3];      //�Z���̉摜���X�g
	const int m_cellsiz = 8;
};