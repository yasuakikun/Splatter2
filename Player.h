#pragma once
#include "GamePlayingScene.h"
#include "CharacterObject.h"
#include "Geometry.h"
#include <string>

class GamePlayingScene;
class peripheral;
class Camera;

enum class AttackType {
	AttackNon,	//�U�����Ă��Ȃ�
	Punch,		//�p���`
	Kick,		//�L�b�N
	Sliding		//�X���C�f�B���O
};

class Player : public CharacterObject
{
	friend GamePlayingScene;

private:
	bool isAerial;	//�W�����v��(true�ŋ�)
	AttackType attack;	//�U���^�C�v
	int weitTimer;	//�_���[�W����

	int noDamage;	//�f�o�b�O�p

	Camera& camera;	//�J����

	//�����_�����
	void Neutral();	//�j���[�g����
	void Walk();	//����
	void Jump();	//�W�����v
	void Crouch();	//���Ⴊ��
	void Punch();	//�p���`
	void Kick();	//�L�b�N
	void Damage();	//�_���[�W
	void Sliding();	//�X���C�f�B���O

	void OnGround(int ground);	//���n


	//�����o�֐��|�C���^(�����_��)
	void (Player::*updater)(const peripheral&);	//�A�b�v�f�[�^

	//���(�X�e�[�g)�ɂ�����֐�
	//�j���[�g����
	void NeutralUpdate(const peripheral&);

	//����
	void WalkUpdate(const peripheral&);

	//�W�����v
	void JumpUpdate(const peripheral&);

	//���n
	void GroundUpdate(const peripheral&);

	//���Ⴊ��
	void CrouchUpdate(const peripheral&);

	//�p���`
	void PunchUpdate(const peripheral&);

	//�L�b�N
	void KickUpdate(const peripheral&);

	//�_���[�W��
	void DamageUpdate(const peripheral&);

	//�X���C�f�B���O
	void SlidingUpdate(const peripheral&);

public:
	Player(Camera& _camera);
	~Player();

	//�A�b�v�f�[�g
	void Update(peripheral& p);
	void Draw();

	const AttackType GetAttackType() const;
};
