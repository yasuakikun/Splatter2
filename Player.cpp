#include "Game.h"
#include "peripheral.h"
#include "Camera.h"
#include "Player.h"
#include <DxLib.h>

const float g = 0.5f;

const char* player_action_path = "Action/player.act";

Player::Player(Camera& _camera) : CharacterObject(), camera(_camera), isAerial(false), attack(AttackType::AttackNon), weitTimer(0), noDamage(0)
{
	CharacterObject::ReadActionFile(player_action_path);

	charactorImg = DxLib::LoadGraph(actData.imgFilePath.c_str());

	updater = &Player::NeutralUpdate;

	pos = { 340.0f, 340.0f };

	currentActionName = "Walk";
}

Player::~Player()
{
}

void Player::Update(peripheral& p)
{
	--noDamage;

	(this->*updater)(p);

	//移動
	pos += vel;

	if (isAerial)
	{
		vel.y += g;
	}
}

void Player::Draw()
{
	Game& game = Game::Instance();

	auto& actInfo = actData.actInfo[currentActionName];	//今の再生アニメーション
	auto& cut = actInfo.cuts[currentCutIdx];	//今のアニメーションの何番目か？
	auto& loop = actInfo.isLoop;	//今のアニメーションがループ再生かどうか
	auto& rc = cut.rc;
	auto centerX = isTurn ? rc.Wigth() - cut.center.x : cut.center.x;

	Position2f _pos = camera.CalculatePosition(pos);

	//プレイヤー描画 
	DxLib::DrawRectRotaGraph2((int)_pos.x, (int)_pos.y, rc.Left(), rc.Top(), rc.Wigth(), rc.Height(), centerX, cut.center.y, game.GetObjectScale(), 0.0, charactorImg, true, isTurn);

	//当たり矩形表示
	RectDraw();

	//デバッグ表示
	int posX = (int)pos.x;
	DrawFormatString(0, 0, 0xffffff, "%d", posX);
}

const AttackType Player::GetAttackType() const
{
	return attack;
}

//ニュートラル
void Player::Neutral()
{
	ChangeAction("Walk");
	attack = AttackType::AttackNon;
	updater = & Player::NeutralUpdate;
}

//歩く
void Player::Walk()
{
	attack = AttackType::AttackNon;
	updater = & Player::WalkUpdate;
}

//ジャンプ
void Player::Jump()
{
	vel.y = -10.0f;
	isAerial = true;
	ChangeAction("Jump");
	attack = AttackType::AttackNon;
	updater = & Player::JumpUpdate;
}

//しゃがみ
void Player::Crouch()
{
	vel.x = 0.0f;
	ChangeAction("Crouch");
	attack = AttackType::AttackNon;
	updater = & Player::CrouchUpdate;
}

//パンチ
void Player::Punch()
{
	vel.x = 0.0f;
	ChangeAction("Punch");
	attack = AttackType::Punch;
	updater = &Player::PunchUpdate;
}

//キック
void Player::Kick()
{
	ChangeAction("Kick");
	attack = AttackType::Kick;
	updater = & Player::KickUpdate;
}

//ダメージ
void Player::Damage()
{
	if (noDamage <= 0)
	{
		weitTimer = 40;
		vel.x = 0.0f;
		ChangeAction("Damage");
		attack = AttackType::AttackNon;
		updater = &Player::DamageUpdate;
	}
	else
	{
	}
	
}

//スライディング
void Player::Sliding()
{
	vel.x = 0.0f;
	ChangeAction("Sliding");
	attack = AttackType::Sliding;
	updater = & Player::SlidingUpdate;
}

//着地処理
void Player::OnGround(int ground)
{
	if (weitTimer > 0)
	{
		vel.y = 0;
		pos.y = (float)ground;
		isAerial = false;
		return;
	}

	vel.y = 0;
	ChangeAction("Ground");
	pos.y = (float)ground;
	isAerial = false;
	updater = & Player::GroundUpdate;
}

//ニュートラル
void Player::NeutralUpdate(const peripheral & p)
{
	if (p.IsPressing(PAD_INPUT_LEFT))
	{
		isTurn = true;
		vel.x = -2.0f;
		Walk();
	}
	else if (p.IsPressing(PAD_INPUT_RIGHT))
	{
		isTurn = false;
		vel.x = 2.0f;
		Walk();
	}
	else if (p.IsPressing(PAD_INPUT_DOWN))
	{
		Crouch();
	}
	else
	{
		vel.x = 0;
		updater = &Player::NeutralUpdate;
	}

	//ジャンプ
	if (p.IsTrigger(PAD_INPUT_1) && (isAerial == false))
	{
		Jump();
	}
	//パンチ
	if (p.IsTrigger(PAD_INPUT_2))
	{
		Punch();
	}
}

//歩き
void Player::WalkUpdate(const peripheral & p)
{
	ProceedAnimationFrame();

	if (p.IsPressing(PAD_INPUT_LEFT))
	{
		isTurn = true;
		vel.x = -2.0f;
		Walk();
	}
	else if (p.IsPressing(PAD_INPUT_RIGHT))
	{
		isTurn = false;
		vel.x = 2.0f;
		Walk();
	}
	else
	{
		vel.x = 0.0f;
		updater = &Player::NeutralUpdate;
	}

	//ジャンプ
	if (p.IsTrigger(PAD_INPUT_1) && (isAerial == false))
	{
		Jump();
	}
	//パンチ
	if (p.IsTrigger(PAD_INPUT_2))
	{
		Punch();
	}
}

//ジャンプ
void Player::JumpUpdate(const peripheral & p)
{
	ProceedAnimationFrame();

	if (p.IsPressing(PAD_INPUT_LEFT))
	{
		isTurn = true;
		vel.x = -1.5f * 0.8f;
	}
	else if (p.IsPressing(PAD_INPUT_RIGHT))
	{
		isTurn = false;
		vel.x = 1.5f * 0.8f;
	}

	if (p.IsPressing(PAD_INPUT_DOWN))
	{
		//キック
		if (p.IsTrigger(PAD_INPUT_2))
		{
			Kick();
		}
	}
}

//着地
void Player::GroundUpdate(const peripheral & p)
{
	if (ProceedAnimationFrame())
	{
		Neutral();
	}

	if (p.IsPressing(PAD_INPUT_DOWN) && (p.IsTrigger(PAD_INPUT_2)))
	{
		Sliding();
	}
}

//しゃがみ
void Player::CrouchUpdate(const peripheral & p)
{
	ProceedAnimationFrame();

	if (p.IsPressing(PAD_INPUT_LEFT))
	{
		vel.x = 0.0f;
		isTurn = true;
		
	}
	else if (p.IsPressing(PAD_INPUT_RIGHT))
	{
		vel.x = 0.0f;
		isTurn = false;
	}

	if(!p.IsPressing(PAD_INPUT_DOWN))
	{
		Neutral();
	}

	if (p.IsTrigger(PAD_INPUT_2))
	{
		Kick();
	}
}

//パンチ
void Player::PunchUpdate(const peripheral &)
{
	if (ProceedAnimationFrame())
	{
		Neutral();
	}
}

//キック
void Player::KickUpdate(const peripheral & p)
{
	if (ProceedAnimationFrame())
	{
		if (isAerial)
		{
			Crouch();
		}
		else
		{
			if (p.IsPressing(PAD_INPUT_DOWN))
			{
				Crouch();
			}
			else
			{
				Neutral();
			}
			
		}
	}
}

//ダメージ
void Player::DamageUpdate(const peripheral &)
{
	if (weitTimer <= 0)
	{
		noDamage = 60;
		Neutral();
	}
	else
	{
		--weitTimer;
		pos.x += isTurn ? 1 : -1;
	}
}

//スライディング
void Player::SlidingUpdate(const peripheral & p)
{
	vel.x = isTurn == true ? -2.5f : 2.5f;

	if (ProceedAnimationFrame())
	{
		if (p.IsPressing(PAD_INPUT_DOWN))
		{
			Crouch();
		}
		else
		{
			Neutral();
		}
	}
}
