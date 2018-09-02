#include "Player.h"
#include "DxLib.h"

Player::Player()
	:m_hp(10), m_px(0), m_py(0), m_face(0), m_reloadtime(6), m_move_flag(false), m_shot_flag(false)
{
	//‰æ‘œ‚ð32*32‚É•ªŠ„‚µ‚Ä“Ç‚Ýž‚Þ
	LoadDivGraph("Image\\player.png", 4, 4, 1, 32, 32, m_playerImg);
}

void Player::update(Cellfield *c, Keyboard Key) {
	m_hp -= c->damage(m_px / 8, m_py / 8);
	if (m_hp <= 0) {
		//GAMEOVER
	}
	if (m_shot_flag) {
		m_shot_flag = false;
	}
	else {
		if (Key.Keyboard_Get(KEY_INPUT_SPACE) != 0) {
			if (m_reloadtime == 7) {
				c->shot(m_px / 8, m_py / 8, m_face);
				m_shot_flag = true;
				m_reloadtime = 0;
			}
		}
		else {
			if (Key.Keyboard_Get(KEY_INPUT_UP) > 0) {
				m_py -= 8;
				m_face = 0;
				m_move_flag = true;
			}
			if (Key.Keyboard_Get(KEY_INPUT_DOWN) > 0) {
				m_py += 8;
				m_face = 2;
				m_move_flag = true;
			}
			if (Key.Keyboard_Get(KEY_INPUT_LEFT) > 0) {
				m_px -= 8;
				m_face = 3;
				m_move_flag = true;
			}
			if (Key.Keyboard_Get(KEY_INPUT_RIGHT) > 0) {
				m_px += 8;
				m_face = 1;
				m_move_flag = true;
			}
		}
	}
	if (Key.Keyboard_Get(KEY_INPUT_DOWN) == 0 && Key.Keyboard_Get(KEY_INPUT_UP) == 0 && Key.Keyboard_Get(KEY_INPUT_LEFT) == 0 && Key.Keyboard_Get(KEY_INPUT_RIGHT) == 0)
		m_move_flag = false;
	if (m_reloadtime < 7)m_reloadtime++;
}

void Player::draw() {
	DrawGraph(m_px, m_py, m_playerImg[m_face], TRUE);
}

void Player::reset() {
	m_hp = 10, m_px = 0, m_py = 0, m_face = 0, m_reloadtime = 6, m_move_flag = false, m_shot_flag = false;
}

void Player::show_state() {
	DrawFormatString(900, 200, GetColor(255, 255, 255), "HP %d", m_hp);
}