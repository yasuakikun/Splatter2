#pragma once
#include "GamePlayingScene.h"
#include "CharacterObject.h"
#include "Geometry.h"
#include <string>

class GamePlayingScene;
class peripheral;
class Camera;

enum class AttackType {
	AttackNon,	//攻撃していない
	Punch,		//パンチ
	Kick,		//キック
	Sliding		//スライディング
};

class Player : public CharacterObject
{
	friend GamePlayingScene;

private:
	bool isAerial;	//ジャンプ中(trueで空中)
	AttackType attack;	//攻撃タイプ
	int weitTimer;	//ダメージ時間

	int noDamage;	//デバッグ用

	Camera& camera;	//カメラ

	//ラムダ式代入
	void Neutral();	//ニュートラル
	void Walk();	//歩く
	void Jump();	//ジャンプ
	void Crouch();	//しゃがみ
	void Punch();	//パンチ
	void Kick();	//キック
	void Damage();	//ダメージ
	void Sliding();	//スライディング

	void OnGround(int ground);	//着地


	//メンバ関数ポインタ(ラムダ式)
	void (Player::*updater)(const peripheral&);	//アップデータ

	//状態(ステート)にあたる関数
	//ニュートラル
	void NeutralUpdate(const peripheral&);

	//歩き
	void WalkUpdate(const peripheral&);

	//ジャンプ
	void JumpUpdate(const peripheral&);

	//着地
	void GroundUpdate(const peripheral&);

	//しゃがみ
	void CrouchUpdate(const peripheral&);

	//パンチ
	void PunchUpdate(const peripheral&);

	//キック
	void KickUpdate(const peripheral&);

	//ダメージ中
	void DamageUpdate(const peripheral&);

	//スライディング
	void SlidingUpdate(const peripheral&);

public:
	Player(Camera& _camera);
	~Player();

	//アップデート
	void Update(peripheral& p);
	void Draw();

	const AttackType GetAttackType() const;
};
