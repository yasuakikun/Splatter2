#pragma once
#include "Geometry.h"
#include<string>
#include <vector>
#include <map>

enum class RectType {
	anchor,	//アンカー?
	attack,	//攻撃矩形
	damage	//やられ矩形
};

///アクション矩形定義 
struct ActRect {
	RectType rt;//矩形種別 
	Rect rc;	//矩形情報 
};

//切り抜きデータ
struct CutInfo {
	Rect rc;				//切り抜き矩形
	Position2 center;		//中心点
	unsigned int duration;	//表示時間
	std::vector<ActRect> actrects;	//アクション矩形 
};//データ量44バイト

typedef std::vector<CutInfo> CutInfoes_t;

struct ActionInfo {
	bool isLoop;
	CutInfoes_t cuts;
};

struct ActionData {
	std::string imgFilePath;
	std::map<std::string, ActionInfo> actInfo;
};

class CharacterObject
{
protected:
	Position2f pos;	//各キャラの座標
	Vector2f vel;	//各キャラの移動速度
	int charactorImg;	//各キャラの画像
	std::string currentActionName;	//現在再生中のアクション名 
	unsigned int currentCutIdx;	//現在表示中のカットインデックス 
	unsigned int frame;	//経過フレーム
	bool isTurn;	//反転フラグ

	void ChangeAction(const char* actionName);	//アクション変更

	bool ProceedAnimationFrame();	//アニメーションフレームを1進める

	void RectDraw();

	ActionData actData;

	void ReadActionFile(const char* actionFile);	//アクションデータのマップ

													//キャラの所持内容をコピー
	void Copy(const CharacterObject& c);

public:
	CharacterObject();
	virtual ~CharacterObject();

	Rect GetActualRectForAction(const Rect & rc);

	const Position2f GetPosition() const;

	const std::vector<ActRect> GetActionRects() const;

};
