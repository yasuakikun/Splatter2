#pragma once
#include "Enemy.h"

class Camera;
class Player;
class EnemyFactory;

class Deadman :
	public Enemy
{
private:
	int weitTimer;	//ダメージ時間

	Camera& camera;
	const Player& player;

	//ラムダ式へ代入
	void Neutral();	//ニュートラル
	void Walk();	//歩く
	void OnDamage();//ダメージ
	void Die();		//死亡

					//メンバ関数ポインタ(ラムダ式)
	void (Deadman::*updater)();	//アップデータ

								//状態(ステート)にあたる関数
								//ニュートラル
	void NeutralUpdate();

	//歩き
	void WalkUpdate();

	//ダメージ中
	void DamageUpdate();

	//死亡
	void DieUpdate();

	friend EnemyFactory;
	//シングルトン
	Deadman(const Player& _player, Camera& _camera);
	Deadman(const Deadman& d);
	void operator= (const Deadman& d);

public:
	~Deadman();

	void Update();
	void Draw();

	Enemy* Clone();
};
