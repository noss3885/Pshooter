#pragma once
class Keyboard
{
public:
	Keyboard();
	int gpUpdatekey();
	int Keyboard_Get(int KeyCode);
	~Keyboard();

private:
	int m_Key[256];  //�L�[���͂��󂯎�郊�X�g
};