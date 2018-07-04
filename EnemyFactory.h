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

//Legion = ƒŒƒMƒIƒ“
typedef std::list<Enemy*> Legion;

class EnemyFactory
{
private:
	int readX;

	Camera & camera;
	const Player& player;
	Stage& stage;

	//ƒŒƒMƒIƒ“
	Legion legion;

	//ˆê”ÔÅ‰‚Ì“G‚Ìƒf[ƒ^
	std::map<std::string, Enemy*> originalEnemy;

public:
	EnemyFactory(const Player& _player, Camera& _camera, Stage& _stage);
	~EnemyFactory();

	void Update();

	Enemy* Create(const char* enemyName, const Position2f pos);

	//“GW‡‘Ì‚ğ•Ô‚· 
	Legion& GetLegion();
};
