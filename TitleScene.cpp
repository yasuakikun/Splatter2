#include "Game.h"
#include "TitleScene.h"
#include "GamePlayingScene.h"
#include <DxLib.h>

TitleScene::TitleScene() : game(Game::Instance()), fadeTimer(255), buttonTimer(0)
{
	titleImg = DxLib::LoadGraph("img/title.png");

	uiImg = DxLib::LoadGraph("img/pressstart.png");

	DxLib::SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	updater = &TitleScene::FadeinUpdate;
}

TitleScene::~TitleScene()
{
}

void TitleScene::Update(peripheral& p)
{
	++buttonTimer;

	(this->*updater)(p);
}

void TitleScene::FadeinUpdate(peripheral & p)
{
	fadeTimer = max(fadeTimer - 1, 0);

	DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - fadeTimer);

	DxLib::DrawGraph(0, 0, titleImg, true);

	if (buttonTimer % 60 < 30)
	{
		DxLib::DrawGraph(200, 340, uiImg, true);
	}

	DxLib::SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	if ((fadeTimer <= 0) || (p.IsTrigger(PAD_INPUT_8)))
	{
		fadeTimer = 0;
		updater = &TitleScene::NormalUpdate;
	}
}

void TitleScene::NormalUpdate(peripheral & p)
{
	DxLib::SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	if (buttonTimer % 60 < 30)
	{
		DxLib::DrawGraph(200, 340, uiImg, true);
	}

	DxLib::DrawGraph(0, 0, titleImg, true);

	if (p.IsTrigger(PAD_INPUT_8))
	{
		updater = &TitleScene::FadeoutUpdate;
	}
}

void TitleScene::FadeoutUpdate(peripheral & p)
{
	fadeTimer = min(fadeTimer + 1, 255);

	DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - fadeTimer);

	DxLib::DrawGraph(0, 0, titleImg, true);

	if (buttonTimer % 4 < 2)
	{
		DxLib::DrawGraph(200, 340, uiImg, true);
	}

	DxLib::SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//ƒV[ƒ“ˆÚs
	if ((fadeTimer >= 255) || (p.IsTrigger(PAD_INPUT_8)))
	{
		game.ChangeScene(new GamePlayingScene());
	}
}
