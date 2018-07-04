#pragma once
#include "Enemy.h"

class Camera;
class Player;
class EnemyFactory;

class Pike :
	public Enemy
{
private:
	int weitTimer;	//次の攻撃までの待ち時間

	Camera& camera;
	const Player& player;

	//ラムダ式へ代入
	void Neutral();	//ニュートラル
	void Attack();	//攻撃

	void OnDamage();//ダメージ

	//メンバ関数ポインタ(ラムダ式)
	void (Pike::*updater)();	//アップデータ

	//状態(ステート)にあたる関数
	//ニュートラル
	void NeutralUpdate();

	//攻撃
	void AttackUpdate();

	friend EnemyFactory;
	//シングルトン
	Pike(const Player& _player, Camera& _camera);
	Pike(const Pike& pike);
	void operator= (const Pike& pike);

public:
	~Pike();

	void Update();
	void Draw();

	Enemy* Clone();
};
