#include<DxLib.h>
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<string>
#include<vector>
#include"Keyboard.h"
#include"SceneMgr.h"

using namespace std;

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// 画面モードの設定
	SetGraphMode(1000, 800, 16);
	ChangeWindowMode(true);

	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	SetDrawScreen(DX_SCREEN_BACK);   //描画先を裏画面に設定

	SceneMgr sceneMgr;
	sceneMgr.Initialize();
	Keyboard keyboard;

	while (ProcessMessage() == 0 && ScreenFlip() == 0 && keyboard.gpUpdatekey() == 0 && ClearDrawScreen() == 0) {
		
		sceneMgr.Update();  //更新
		sceneMgr.Draw();    //描画

		if (keyboard.Keyboard_Get(KEY_INPUT_ESCAPE) != 0)
		{
			//break;
		}
	}

	sceneMgr.Finalize();

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了
}