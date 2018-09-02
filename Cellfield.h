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
	std::vector<std::vector<int> > m_data;  //セルの場の情報を保存
	int m_XMAX, m_YMAX;    //セルの場の幅と高さ
	int m_cellImg[3];      //セルの画像リスト
	const int m_cellsiz = 8;
};