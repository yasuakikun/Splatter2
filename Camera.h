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
	const Stage& stage;	//�X�e�[�W���
	Rect rect;
public:
	Camera(const Stage& _stage);
	~Camera();

	void Update();

	//�t�H�[�J�X���ׂ��L�����N�^�[�I�u�W�F�N�g���Z�b�g
	void SetFocus(std::shared_ptr<CharacterObject> c);

	//
	Position2f CalculatePosition(Position2f pPos);

	//�J�����̍��W��Ԃ�
	const Position2f& GetPosition()const;

	//���݌����Ă���͈͂�Ԃ�
	Rect& GetViewport();
};
