#pragma once

#include "Cellfield.h"
#include "Keyboard.h"

class Player
{
public:
	Player();
	void update(Cellfield *c, Keyboard Key);
	void draw();
	void reset();
	void show_state();

private:
	int m_hp;
	int m_px, m_py;
	int m_playerImg[4];
	int m_face;
	int m_reloadtime;
	bool m_move_flag;
	bool m_shot_flag;
};
