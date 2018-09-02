#include "Game.h"
#include "DxLib.h"

Game::Game(ISceneChanger* changer) : BaseScene(changer) {
}

//初期化
void Game::Initialize() {
	char String[10000];
	int FileHandle = FileRead_open("Stage\\teststage.txt");
	FileRead_gets(String, 10000, FileHandle);

	time = GetCurrentTime();
	cell.set(String, 99, 99);
	Player player;
}

//更新
void Game::Update() {
	keyboard.gpUpdatekey();
	if (CheckHitKey(KEY_INPUT_ESCAPE) != 0) { //Escキーが押されていたら
		mSceneChanger->ChangeScene(eScene_Menu);//シーンをメニューに変更
	}
	if (GetCurrentTime() - time > 75) {
		time = GetCurrentTime();
		player.update(&cell, keyboard);
		cell.update();
	}
}

//描画
void Game::Draw() {
	BaseScene::Draw();//親クラスの描画メソッドを呼ぶ
	cell.draw();
	player.draw();
	player.show_state();
}