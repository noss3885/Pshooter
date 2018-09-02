#include<DxLib.h>
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<string>
#include<vector>
#include"Keyboard.h"
#include"SceneMgr.h"

using namespace std;

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// ��ʃ��[�h�̐ݒ�
	SetGraphMode(1000, 800, 16);
	ChangeWindowMode(true);

	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}

	SetDrawScreen(DX_SCREEN_BACK);   //�`���𗠉�ʂɐݒ�

	SceneMgr sceneMgr;
	sceneMgr.Initialize();
	Keyboard keyboard;

	while (ProcessMessage() == 0 && ScreenFlip() == 0 && keyboard.gpUpdatekey() == 0 && ClearDrawScreen() == 0) {
		
		sceneMgr.Update();  //�X�V
		sceneMgr.Draw();    //�`��

		if (keyboard.Keyboard_Get(KEY_INPUT_ESCAPE) != 0)
		{
			//break;
		}
	}

	sceneMgr.Finalize();

	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I��
}