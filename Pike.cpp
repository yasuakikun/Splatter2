#include "Camera.h"
#include "EnemyFactory.h"
#include "Player.h"
#include "Pike.h"
#include <DxLib.h>

const char* Pike_action_path = "Action/pike.act";

Pike::Pike(const Player& _player, Camera& _camera) : Enemy(_player), player(_player), camera(_camera), weitTimer(0)
{
	CharacterObject::ReadActionFile(Pike_action_path);

	charactorImg = DxLib::LoadGraph(actData.imgFilePath.c_str());

	updater = &Pike::NeutralUpdate;

	ChangeAction("Attack");
}

Pike::Pike(const Pike& pike) : Enemy(pike.player), player(pike.player), camera(pike.camera)
{
	*this = pike;
}

void Pike::operator=(const Pike & pike)
{
	this->Copy(pike);
	updater = pike.updater;
	vel = pike.vel;
	weitTimer = pike.weitTimer;
}

Enemy * Pike::Clone()
{
	return new Pike(*this); ;
}

Pike::~Pike()
{
}

void Pike::Update()
{
	(this->*updater)();
}

void Pike::Draw()
{
	auto& actInfo = actData.actInfo[currentActionName];
	auto& cut = actInfo.cuts[currentCutIdx];
	auto& loop = actInfo.isLoop;
	auto& rc = cut.rc;

	Position2f _pos = camera.CalculatePosition(pos);

	DrawRectRotaGraph2((int)_pos.x, (int)_pos.y, cut.rc.Left(), cut.rc.Top(), cut.rc.Wigth(), cut.rc.Height(), cut.center.x, cut.center.y, 2.0f, 0.0f, charactorImg, true, isTurn);

	//当たり矩形表示
	RectDraw();
}

void Pike::Neutral()
{
	weitTimer = 0;
	updater = &Pike::NeutralUpdate;
}

void Pike::Attack()
{
	currentCutIdx = 0;
	frame = 0;
	updater = & Pike::AttackUpdate;
}

void Pike::OnDamage()
{
	//Pikeはダメージを受けない
}

//ニュートラル
void Pike::NeutralUpdate()
{
	if (weitTimer <= 0)
	{
		Attack();
	}
	else
	{
		--weitTimer;
	}
}

void Pike::AttackUpdate()
{
	if (frame < actData.actInfo[currentActionName].cuts[currentCutIdx].duration)
	{
		++frame;
	}
	else
	{
		frame = 0;
		if (currentCutIdx < actData.actInfo[currentActionName].cuts.size() - 1)
		{
			++currentCutIdx;
		}
		else
		{
			Neutral();
		}
	}
}
