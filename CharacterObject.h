#pragma once
#include "Geometry.h"
#include<string>
#include <vector>
#include <map>

enum class RectType {
	anchor,	//�A���J�[?
	attack,	//�U����`
	damage	//�����`
};

///�A�N�V������`��` 
struct ActRect {
	RectType rt;//��`��� 
	Rect rc;	//��`��� 
};

//�؂蔲���f�[�^
struct CutInfo {
	Rect rc;				//�؂蔲����`
	Position2 center;		//���S�_
	unsigned int duration;	//�\������
	std::vector<ActRect> actrects;	//�A�N�V������` 
};//�f�[�^��44�o�C�g

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
	Position2f pos;	//�e�L�����̍��W
	Vector2f vel;	//�e�L�����̈ړ����x
	int charactorImg;	//�e�L�����̉摜
	std::string currentActionName;	//���ݍĐ����̃A�N�V������ 
	unsigned int currentCutIdx;	//���ݕ\�����̃J�b�g�C���f�b�N�X 
	unsigned int frame;	//�o�߃t���[��
	bool isTurn;	//���]�t���O

	void ChangeAction(const char* actionName);	//�A�N�V�����ύX

	bool ProceedAnimationFrame();	//�A�j���[�V�����t���[����1�i�߂�

	void RectDraw();

	ActionData actData;

	void ReadActionFile(const char* actionFile);	//�A�N�V�����f�[�^�̃}�b�v

													//�L�����̏������e���R�s�[
	void Copy(const CharacterObject& c);

public:
	CharacterObject();
	virtual ~CharacterObject();

	Rect GetActualRectForAction(const Rect & rc);

	const Position2f GetPosition() const;

	const std::vector<ActRect> GetActionRects() const;

};
