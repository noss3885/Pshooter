#pragma once
#include "BaseScene.h"
#include "ISceneChanger.h"
#include "Cellfield.h"
#include "Player.h"

//�Q�[����ʃN���X
class Game : public BaseScene {

public:
	Game(ISceneChanger* changer);
	void Initialize() override;    //�������������I�[�o�[���C�h�B
								   //void Finalize() override;        //�I���������I�[�o�[���C�h�B
	void Update() override;        //�X�V�������I�[�o�[���C�h�B
	void Draw() override;            //�`�揈�����I�[�o�[���C�h�B

	int time;
	Cellfield cell;
	Player player;
	Keyboard keyboard;
};