#pragma once
#include "Scene.h"

class peripheral;

class GameOverScene :
	public Scene
{
private:
	int gameoverImg;
	int uiImg;
	int fadeTimer;	//フェード中タイマー
	int buttonTimer;//ボタンの点滅タイマー

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

