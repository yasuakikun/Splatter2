#include "Game.h"
#include "GamePlayingScene.h"
#include "GameContinueScene.h"
#include "GameOverScene.h"
#include "Geometry.h"
#include <DxLib.h>

const Vector2 CountImgSize = { 585, 318 };
const Vector2 CutSize = { 117, 159 };

GameContinueScene::GameContinueScene() : game(Game::Instance()), frame(0)
{
	continueCntImg = DxLib::LoadGraph("img/count.png");

	DxLib::SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

GameContinueScene::~GameContinueScene()
{
}

void GameContinueScene::Update(peripheral& p)
{
	auto cnt = frame / 90;
	Vector2 centerPos = { (768 / 2), (448 / 2) };
	auto drawImgPosX = (cnt * CutSize.x) % CountImgSize.x;
	auto drawImgPosY = ((cnt * CutSize.x) / CountImgSize.x) * CutSize.y;

	DxLib::DrawRectGraph(centerPos.x - (CutSize.x / 2), centerPos.y - (CutSize.y / 2), drawImgPosX, drawImgPosY, CutSize.x, CutSize.y,continueCntImg, true, false);
	//Dest = pos,
	//Src = Img‚Ì‰æ‘œã‚Å‚Ì•`‰æˆÊ’u‚Ì¶ã

	++frame;

	if (frame >= 900 - 1)
	{
		game.ChangeScene(new GameOverScene());
	}
	else if ((p.IsTrigger(PAD_INPUT_1)) || (p.IsTrigger(PAD_INPUT_2)))
	{
		frame = ((frame / 90) + 1) * 90;
	}

	if (p.IsTrigger(PAD_INPUT_8))
	{
		game.ChangeScene(new GamePlayingScene());
	}
}
