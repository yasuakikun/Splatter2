#pragma once
#include "CharacterObject.h"
#include "Geometry.h"

class EnemyFactory;
class Player;

class Enemy :
	public CharacterObject
{
	friend EnemyFactory;

protected:
	const Player& player;
	virtual Enemy* Clone() = 0;

	Enemy(const Player& p);

public:
	virtual~Enemy();

	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void OnDamage() = 0;

	Position2f GetPosition();	//現在のポジション
};

/*
//敵の種類
・〇デッドマン
・　トップベビー
・〇バット
・　バイキングデッド
・　ウォーターデッド
・　イビルドッグ
・　ノブー
・　カラス
・　ジョーカー
・　マスターデッド
・　オウァ
・　リバイバルデッド
・　ジュラル星人(ファイヤーデッド)
*/