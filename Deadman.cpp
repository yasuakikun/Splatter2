#include "Camera.h"
#include "EnemyFactory.h"
#include "Player.h"
#include "Deadman.h"
#include <DxLib.h>

const char* deadman_action_path = "Action/deadman.act";

Deadman::Deadman(const Player& _player, Camera& _camera) : Enemy(_player), player(_player), camera(_camera), weitTimer(0)
{
	CharacterObject::ReadActionFile(deadman_action_path);

	charactorImg = DxLib::LoadGraph(actData.imgFilePath.c_str());

	updater = &Deadman::NeutralUpdate;

	ChangeAction("Walk");
}

Deadman::Deadman(const Deadman& d) : Enemy(d.player), player(d.player), camera(d.camera)
{
	*this = d;
}

void Deadman::operator=(const Deadman & d)
{
	this->Copy(d);
	updater = d.updater;
	vel = d.vel;
}

Enemy * Deadman::Clone()
{
	return new Deadman(*this); ;
}

Deadman::~Deadman()
{
}

void Deadman::Update()
{
	(this->*updater)();

	pos += vel;
}

void Deadman::Draw()
{
	auto& actInfo = actData.actInfo[currentActionName];
	auto& cut = actInfo.cuts[currentCutIdx];
	auto& loop = actInfo.isLoop;
	auto& rc = cut.rc;

	auto centerX = isTurn ? rc.Wigth() - cut.center.x : cut.center.x;

	Position2f _pos = camera.CalculatePosition(pos);

	DrawRectRotaGraph2((int)_pos.x, (int)_pos.y, cut.rc.Left(), cut.rc.Top(), cut.rc.Wigth(), cut.rc.Height(), cut.center.x, cut.center.y, 2.0f, 0.0f, charactorImg, true, isTurn);

	//当たり矩形表示
	RectDraw();
}

void Deadman::Neutral()
{
	ChangeAction("Walk");
	currentCutIdx = 0;
	frame = 0;
	updater = &Deadman::NeutralUpdate;
}

void Deadman::Walk()
{
	ChangeAction("Walk");
	currentCutIdx = 0;
	frame = 0;
	updater = &Deadman::WalkUpdate;
}

void Deadman::OnDamage()
{
	vel = { 0.0f, 0.0f };
	currentCutIdx = 0;
	frame = 0;

	if (player.GetAttackType() == AttackType::Punch)
	{
		ChangeAction("Damage");
		updater = &Deadman::DamageUpdate;
	}
	else if (player.GetAttackType() != AttackType::AttackNon)
	{
		ChangeAction("Die2");
		updater = &Deadman::DieUpdate;
	}
}

void Deadman::Die()
{
	vel = { 0.0f, 0.0f };
	ChangeAction("Die");
	currentCutIdx = 0;
	frame = 0;
	updater = &Deadman::DieUpdate;
}

//ニュートラル
void Deadman::NeutralUpdate()
{
	auto playerPos = player.GetPosition();

	if (player.GetPosition().x >= pos.x)
	{
		isTurn = false;
		weitTimer = 60;
		Walk();
	}
	else
	{
		isTurn = true;
		weitTimer = 60;
		Walk();
	}
}

//歩き
void Deadman::WalkUpdate()
{
	vel.x = isTurn ? -1.0f : +1.0f;

	ProceedAnimationFrame();

	if (weitTimer <= 0)
	{
		Neutral();
	}
	else
	{
		--weitTimer;
	}
}

//ダメージ
void Deadman::DamageUpdate()
{
	if (ProceedAnimationFrame())
	{
		Die();
	}
}

void Deadman::DieUpdate()
{
	if (ProceedAnimationFrame())
	{
		Neutral();
	}
}
