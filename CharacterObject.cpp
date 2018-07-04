#include <cassert>

#include "Game.h"
#include "CharacterObject.h"
#include "DxLib.h"

CharacterObject::CharacterObject() : pos(0.0f, 0.0f), vel(), currentCutIdx(0), frame(0), isTurn(false)
{
}

CharacterObject::~CharacterObject()
{
}

void CharacterObject::ChangeAction(const char* actionName)
{
	currentActionName = actionName;
	currentCutIdx = 0;
	frame = 0;
}

bool CharacterObject::ProceedAnimationFrame()
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
			if (actData.actInfo[currentActionName].isLoop)
			{
				currentCutIdx = 0;
			}
			else
			{
				return true;
			}
		}
	}

	return false;
}

void CharacterObject::RectDraw()
{
	Game& game = Game::Instance();

	auto& actInfo = actData.actInfo[currentActionName];
	auto& cut = actInfo.cuts[currentCutIdx];

	for (auto& act : cut.actrects)
	{
		Rect rect = act.rc;

		auto color = 0;

		if (act.rt == RectType::attack)
		{
			color = 0xff0000;
		}
		else if (act.rt == RectType::damage)
		{
			color = 0x00ff00;
		}

		rect = GetActualRectForAction(rect);

		DrawBox(rect.Left(), rect.Top(), rect.Right(), rect.Bottom(), color, false);
	}
}

Rect CharacterObject::GetActualRectForAction(const Rect & rc)
{
	Game& game = Game::Instance();

	Rect rec = rc;

	rec.center.x = isTurn ? -rc.center.x : rc.center.x;

	rec.center.x = (int)(rec.center.x * game.GetObjectScale()) + (int)pos.x;
	rec.center.y = (int)(rec.center.y * game.GetObjectScale()) + (int)pos.y;
	rec.size.w *= (int)game.GetObjectScale();
	rec.size.h *= (int)game.GetObjectScale();

	return rec;
}

const Position2f CharacterObject::GetPosition() const
{
	return pos;
}

const std::vector<ActRect> CharacterObject::GetActionRects() const
{
	return std::vector<ActRect>(actData.actInfo.at(currentActionName).cuts[currentCutIdx].actrects);
}

void CharacterObject::ReadActionFile(const char * actionFile)
{
	int h = DxLib::FileRead_open(actionFile, false);

	float version = 0.0f;
	DxLib::FileRead_read(&version, sizeof(version), h);

	//アサート
	assert(version == 1.01f && "アクションファイルのバージョンが一致しません");

	int imgPathSize = 0;
	DxLib::FileRead_read(&imgPathSize, sizeof(imgPathSize), h);

	std::string imgPath = "";
	imgPath.resize(imgPathSize);
	DxLib::FileRead_read(&imgPath[0], imgPathSize, h);

	std::string path = actionFile;
	auto ipos = path.find_last_of("/") + 1;
	actData.imgFilePath = path.substr(0, ipos) + imgPath;


	int actionCnt = 0;
	DxLib::FileRead_read(&actionCnt, sizeof(actionCnt), h);

	for (int i = 0; i < actionCnt; ++i)
	{
		//アクション
		int fileNameSize = 0;
		DxLib::FileRead_read(&fileNameSize, sizeof(fileNameSize), h);

		std::string actionName = "";
		actionName.resize(fileNameSize);
		DxLib::FileRead_read(&actionName[0], fileNameSize, h);

		ActionInfo actInfo;
		DxLib::FileRead_read(&actInfo.isLoop, sizeof(actInfo.isLoop), h);

		int cutCount = 0;
		DxLib::FileRead_read(&cutCount, sizeof(cutCount), h);

		//カットデータの読み込み
		actInfo.cuts.resize(cutCount);
		for (int i = 0; i < cutCount; ++i)
		{
			DxLib::FileRead_read(&actInfo.cuts[i], sizeof(actInfo.cuts[i]) - sizeof(actInfo.cuts[i].actrects), h);
			int actRectCnt = 0;
			DxLib::FileRead_read(&actRectCnt, sizeof(actRectCnt), h);

			if (actRectCnt != 0)
			{
				actInfo.cuts[i].actrects.resize(actRectCnt);
				DxLib::FileRead_read(&actInfo.cuts[i].actrects[0], actRectCnt * sizeof(actInfo.cuts[i].actrects[0]), h);
			}
		}

		actData.actInfo[actionName] = actInfo;
	}

	DxLib::FileRead_close(h);
}

void
CharacterObject::Copy(const CharacterObject& c)
{
	//アクションデータのコピー 
	actData.imgFilePath = c.actData.imgFilePath;
	for (auto& info : c.actData.actInfo)
	{
		actData.actInfo[info.first] = info.second;
	}

	isTurn = c.isTurn;	//反転フラグ
	pos = c.pos;	//自分の座標
	vel = c.vel;	//自分の速度
	charactorImg = c.charactorImg;	//自分の画像
	currentActionName = c.currentActionName;	//「今」のアクション名
	currentCutIdx = c.currentCutIdx;	//「今」表示中のカット番号
	frame = c.frame;	//そのカット番号における経過時間
}
