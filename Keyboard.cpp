#include "Keyboard.h"
#include "DxLib.h"

Keyboard::Keyboard()
{
}

//キー状態を更新する
int Keyboard::gpUpdatekey() {
	char tmpKey[256];
	GetHitKeyStateAll(tmpKey);
	for (int i = 0; i < 256; i++) {
		if (tmpKey[i] != 0) {
			m_Key[i]++;
		}
		else {
			m_Key[i] = 0;
		}
	}
	return 0;
}

int Keyboard::Keyboard_Get(int KeyCode) {
	return m_Key[KeyCode]; // KeyCodeの入力状態を返す
}

Keyboard::~Keyboard()
{
}