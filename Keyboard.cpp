#include "Keyboard.h"
#include "DxLib.h"

Keyboard::Keyboard()
{
}

//�L�[��Ԃ��X�V����
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
	return m_Key[KeyCode]; // KeyCode�̓��͏�Ԃ�Ԃ�
}

Keyboard::~Keyboard()
{
}