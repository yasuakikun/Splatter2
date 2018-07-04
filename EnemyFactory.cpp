#include "Stage.h"
#include "Camera.h"
#include "Deadman.h"
#include "Bat.h"
#include "Pike.h"
#include "EnemyFactory.h"
#include <DxLib.h>

EnemyFactory::EnemyFactory(const Player& _player, Camera& _camera, Stage& _stage) : player(_player), camera(_camera), stage(_stage), readX(0)
{
	originalEnemy["deadman"] = new Deadman(_player, _camera);
	originalEnemy["bat"] = new Bat(_player, _camera);
	originalEnemy["pike"] = new Pike(_player, _camera);
}

EnemyFactory::~EnemyFactory()
{
	for (auto itr = EnemyFactory::legion.begin(); itr != EnemyFactory::legion.end();)
	{
		delete(*itr);
		itr = EnemyFactory::legion.erase(itr);
	}
}

void EnemyFactory::Update()
{
	auto enemies = stage.GetEnemySpawnRange(camera.GetViewport().Left(), camera.GetViewport().Right() + 64);

	int y = 0;

	auto& mapSize = stage.GetMapSize();

	const std::string enemyname[] = { "","deadman","bat","pike" };

	for (auto enemy : enemies)
	{
		if (enemyname[enemy] != "")
		{
			EnemyFactory::Create(enemyname[enemy].c_str(), Position2f((readX * 64), y * 48));
		}

		++y;

		if (y >= mapSize.Height())
		{
			++readX;
			y = 0;
		}
	}
}

//¶¬‚µ‚½enemy‚ð•Ô‚·‚ª
//ŽÀÛ‚Í‹ï‘Ì“I‚Èenemy(Deadman)“™‚ª“ü‚Á‚Ä‚¢‚é
Enemy * EnemyFactory::Create(const char* enemyName, const Position2f pos)
{
	if (originalEnemy.find(enemyName) != originalEnemy.end())
	{
		auto enemy = originalEnemy[enemyName]->Clone();
		enemy->pos = pos;
		legion.push_back(enemy);

		return enemy;
	}
	else
	{
		return nullptr;
	}
}

Legion & EnemyFactory::GetLegion()
{
	return legion;
}
