#include "Camera.h"
#include "EnemyFactory.h"
#include "Player.h"
#include "Bat.h"
#include <DxLib.h>

const char* bat_action_path = "Action/Bat.act";

Bat::Bat(const Player& _player, Camera& _camera) : Enemy(_player), player(_player), camera(_camera), weitTimer(0)
{
	CharacterObject::ReadActionFile(bat_action_path);

	charactorImg = DxLib::LoadGraph(actData.imgFilePath.c_str());

	updater = &Bat::NeutralUpdate;

	ChangeAction("Fly");
}

Bat::Bat(const Bat& b) : Enemy(b.player), player(b.player), camera(b.camera)
{
	*this = b;
}

void Bat::operator=(const Bat & b)
{
	this->Copy(b);
	updater = b.updater;
	vel = b.vel;
}

Enemy * Bat::Clone()
{
	return new Bat(*this); ;
}

Bat::~Bat()
{
}

void Bat::Update()
{
	(this->*updater)();

	pos += vel;
}

void Bat::Draw()
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

void Bat::Neutral()
{
	ChangeAction("Fly");
	currentCutIdx = 0;
	frame = 0;
	updater = &Bat::NeutralUpdate;
}

void Bat::Fly()
{
	ChangeAction("Fly");
	currentCutIdx = 0;
	frame = 0;
	updater = &Bat::FlyUpdate;
}

void Bat::OnDamage()
{
	vel = { 0, 0 };
	ChangeAction("Die");
	currentCutIdx = 0;
	frame = 0;
	updater = &Bat::DieUpdate;
}

//ニュートラル
void Bat::NeutralUpdate()
{
	auto playerPos = player.GetPosition();

	if (player.GetPosition().x >= pos.x)
	{
		isTurn = false;
		weitTimer = 60;
		Fly();
	}
	else
	{
		isTurn = true;
		weitTimer = 60;
		Fly();
	}
}

//歩き
void Bat::FlyUpdate()
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
void Bat::DieUpdate()
{
	ProceedAnimationFrame();
}
