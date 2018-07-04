#include "Game.h"
#include "TitleScene.h"
#include "GamePlayingScene.h"
#include "GameContinueScene.h"
#include "GameOverScene.h"
#include "Stage.h"
#include "BackGronud.h"
#include "Camera.h"
#include "Ground.h"
#include "Player.h"
#include "EnemyFactory.h"
#include "Enemy.h"
#include "CollisionDetector.h"
#include <DxLib.h>

GamePlayingScene::GamePlayingScene() : game(Game::Instance())
{
	stage = std::make_shared<Stage>();
	camera = std::make_shared<Camera>(*stage);
	bk = std::make_shared<BackGronud>(*camera);
	pl = std::make_shared<Player>(*camera);
	g = std::make_shared<Ground>();
	factory = std::make_shared<EnemyFactory>(*pl, *camera, *stage);

	camera->SetFocus(pl);

	camera->Update();

	factory->Update();

	/*factory->Create("deadman", { 10.0f, 340.0f });
	factory->Create("deadman", { 750.0f, 340.0f });
	factory->Create("bat", { 10.0f, 200.0f });*/

	

	fadeTimer = 255;

	updater = &GamePlayingScene::FadeinUpdate;

	DxLib::SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

GamePlayingScene::~GamePlayingScene()
{
}

void GamePlayingScene::Update(peripheral& p)
{
	//描画処理

	//背景
	bk->Draw();

	//プレイヤー
	pl->Draw();

	//敵
	for (auto& enemy : factory->GetLegion())
	{
		enemy->Draw();
	}

	DxLib::DrawLine(0, 340, 768, 340, 0x0000ff, false);

	//アップデート

	//敵
	for (auto& enemy : factory->GetLegion())
	{
		enemy->Update();
	}

	//プレイヤー
	pl->Update(p);

	//プレイヤーの着地判定
	auto ground_y = g->GetCurrentGroundY(pl->pos);
	if (pl->pos.y > ground_y)
	{
		pl->OnGround(ground_y);
	}

	//当たり判定
	for (auto& enemy : factory->GetLegion())
	{
		for (auto& playerRect : pl->GetActionRects())
		{
			for (auto& enemyRect : enemy->GetActionRects())
			{
				if ((playerRect.rt == RectType::attack) && (enemyRect.rt == RectType::damage))
				{
					if (CollisionDetector::isCollided(pl->GetActualRectForAction(playerRect.rc), enemy->GetActualRectForAction(enemyRect.rc)))
					{
						enemy->OnDamage();
					}
				}
				else if ((playerRect.rt == RectType::damage) && (enemyRect.rt == RectType::attack))
				{
					if (CollisionDetector::isCollided(pl->GetActualRectForAction(playerRect.rc), enemy->GetActualRectForAction(enemyRect.rc)))
					{
						pl->Damage();
					}
				}
			}
		}
	}

	camera->Update();

	factory->Update();

	//シーン移行
	if (p.IsTrigger(PAD_INPUT_8))
	{
		updater = &GamePlayingScene::FadeoutUpdate;
	}

	(this->*updater)();
}

void GamePlayingScene::FadeinUpdate()
{
	fadeTimer = max(fadeTimer - 1, 0);

	DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeTimer);

	DxLib::DrawBox(0, 0, 768, 448, 0x000000, true);

	DxLib::SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	if (fadeTimer <= 0)
	{
		updater = &GamePlayingScene::NormalUpdate;
	}
}

void GamePlayingScene::NormalUpdate()
{
}

void GamePlayingScene::FadeoutUpdate()
{
	fadeTimer = min(fadeTimer + 1, 255);

	DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeTimer);

	DxLib::DrawBox(0, 0, 768, 448, 0x000000, true);

	DxLib::SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	if (fadeTimer >= 255)
	{
		game.ChangeScene(new GameContinueScene());
	}
}
