#pragma once
#include "Scene.h"

class peripheral;

class GameOverScene :
	public Scene
{
private:
	int gameoverImg;
	int uiImg;
	int fadeTimer;	//�t�F�[�h���^�C�}�[
	int buttonTimer;//�{�^���̓_�Ń^�C�}�[

	Game& game;

public:
	GameOverScene();
	~GameOverScene();

	void Update(peripheral& p);

	void (GameOverScene::*updater)(peripheral& p);

	void FadeinUpdate(peripheral& p);
	void NormalUpdate(peripheral& p);
	void FadeoutUpdate(peripheral& p);
};

