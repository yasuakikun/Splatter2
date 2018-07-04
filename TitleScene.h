#pragma once
#include "Scene.h"

class Game;

class TitleScene :
	public Scene
{
private:
	int titleImg;
	int uiImg;
	int fadeTimer;	//�t�F�[�h���^�C�}�[
	int buttonTimer;//�{�^���̓_�Ń^�C�}�[

	Game& game;

	void (TitleScene::*updater)(peripheral& p);

	void FadeinUpdate(peripheral& p);
	void NormalUpdate(peripheral& p);
	void FadeoutUpdate(peripheral& p);

public:
	TitleScene();
	~TitleScene();

	void Update(peripheral& p);
};

