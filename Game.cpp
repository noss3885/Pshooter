#include "Game.h"
#include "DxLib.h"

Game::Game(ISceneChanger* changer) : BaseScene(changer) {
}

//������
void Game::Initialize() {
	char String[10000];
	int FileHandle = FileRead_open("Stage\\teststage.txt");
	FileRead_gets(String, 10000, FileHandle);

	time = GetCurrentTime();
	cell.set(String, 99, 99);
	Player player;
}

//�X�V
void Game::Update() {
	keyboard.gpUpdatekey();
	if (CheckHitKey(KEY_INPUT_ESCAPE) != 0) { //Esc�L�[��������Ă�����
		mSceneChanger->ChangeScene(eScene_Menu);//�V�[�������j���[�ɕύX
	}
	if (GetCurrentTime() - time > 75) {
		time = GetCurrentTime();
		player.update(&cell, keyboard);
		cell.update();
	}
}

//�`��
void Game::Draw() {
	BaseScene::Draw();//�e�N���X�̕`�惁�\�b�h���Ă�
	cell.draw();
	player.draw();
	player.show_state();
}