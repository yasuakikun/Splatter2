#include "Game.h"
#include "peripheral.h"
#include "TitleScene.h"
#include "GameOverScene.h"
#include <DxLib.h>

GameOverScene::GameOverScene() : game(Game::Instance()),fadeTimer(255), buttonTimer(0)
{
	gameoverImg = DxLib::LoadGraph("img/gameover.png");

	uiImg = DxLib::LoadGraph("img/pressstart.png");

	updater = &GameOverScene::FadeinUpdate;

	DxLib::SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

GameOverScene::~GameOverScene()
{
}

void GameOverScene::Update(peripheral& p)
{
	++buttonTimer;

	(this->*updater)(p);
}

void GameOverScene::FadeinUpdate(peripheral & p)
{
	fadeTimer = max(fadeTimer - 1, 0);

	DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - fadeTimer);

	DxLib::DrawGraph(0, 0, gameoverImg, true);

	if (buttonTimer % 60 < 30)
	{
		DxLib::DrawGraph(200, 340, uiImg, true);
	}

	DxLib::SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	if ((fadeTimer <= 0) || (p.IsTrigger(PAD_INPUT_8)))
	{
		fadeTimer = 0;
		updater = &GameOverScene::NormalUpdate;
	}
}

void GameOverScene::NormalUpdate(peripheral & p)
{
	DxLib::DrawGraph(0, 0, gameoverImg, true);

	if (buttonTimer % 60 < 30)
	{
		DxLib::DrawGraph(200, 340, uiImg, true);
	}

	DxLib::SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	if (p.IsTrigger(PAD_INPUT_8))
	{
		updater = &GameOverScene::FadeoutUpdate;
	}
}

void GameOverScene::FadeoutUpdate(peripheral & p)
{
	fadeTimer = min(fadeTimer + 1, 255);

	DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - fadeTimer);

	DxLib::DrawGraph(0, 0, gameoverImg, true);

	if (buttonTimer % 4 < 2)
	{
		DxLib::DrawGraph(200, 340, uiImg, true);
	}

	DxLib::SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	if (fadeTimer >= 255)
	{
		game.ChangeScene(new TitleScene());
	}
}
