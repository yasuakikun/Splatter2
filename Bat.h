#pragma once
#include "Enemy.h"

class Camera;
class Player;
class EnemyFactory;

class Bat :
	public Enemy
{
private:
	int weitTimer;	//ダメージ時間

	Camera& camera;
	const Player& player;

	//ダメージを受けた場合
	void OnDamage();

	//ラムダ式代入
	void Neutral();	//ニュートラル
	void Fly();		//飛ぶ

					//メンバ関数ポインタ(ラムダ式)
	void (Bat::*updater)();	//アップデータ

							//状態(ステート)にあたる関数
							//ニュートラル
	void NeutralUpdate();

	//飛ぶ
	void FlyUpdate();

	//死亡
	void DieUpdate();

	friend EnemyFactory;
	//シングルトン
	Bat(const Player& _player, Camera& _camera);
	Bat(const Bat& b);
	void operator= (const Bat& b);

public:
	~Bat();

	void Update();
	void Draw();

	Enemy* Clone();
};
