#pragma once
#include "CharacterObject.h"
#include "Geometry.h"
#include "Stage.h"
#include <memory>

class Game;
class CharacterObject;
class Stage;

class Camera
{
private:
	std::weak_ptr<CharacterObject> focus;

	Position2f _pos;

	const Game& game;
	const Stage& stage;	//ステージ情報
	Rect rect;
public:
	Camera(const Stage& _stage);
	~Camera();

	void Update();

	//フォーカスすべきキャラクターオブジェクトをセット
	void SetFocus(std::shared_ptr<CharacterObject> c);

	//
	Position2f CalculatePosition(Position2f pPos);

	//カメラの座標を返す
	const Position2f& GetPosition()const;

	//現在見えている範囲を返す
	Rect& GetViewport();
};
