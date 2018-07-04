#include "EnemyFactory.h"
#include "Enemy.h"

Enemy::Enemy(const Player& p) : CharacterObject(), player(p)/*, vel()*/
{
}

Enemy::~Enemy()
{
}

Position2f Enemy::GetPosition()
{
	return pos;
}
