#pragma once
#include "Scene.h"

class Game;

class TitleScene :
	public Scene
{
private:
	int titleImg;
	int uiImg;
	int fadeTimer;	//フェード中タイマー
	int buttonTimer;//ボタンの点滅タイマー

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

