#pragma once
#include "Geometry.h"
#include "CharacterObject.h"
#include <map>
#include <string>
#include <list>

class Stage;
class Camera;
class Player;
class Enemy;

//Legion = レギオン
typedef std::list<Enemy*> Legion;

class EnemyFactory
{
private:
	int readX;

	Camera & camera;
	const Player& player;
	Stage& stage;

	//レギオン
	Legion legion;

	//一番最初の敵のデータ
	std::map<std::string, Enemy*> originalEnemy;

public:
	EnemyFactory(const Player& _player, Camera& _camera, Stage& _stage);
	~EnemyFactory();

	void Update();

	Enemy* Create(const char* enemyName, const Position2f pos);

	//敵集合体を返す 
	Legion& GetLegion();
};
