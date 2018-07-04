#pragma once
#include "CharacterObject.h"
#include "Geometry.h"

class EnemyFactory;
class Player;

class Enemy :
	public CharacterObject
{
	friend EnemyFactory;

protected:
	const Player& player;
	virtual Enemy* Clone() = 0;

	Enemy(const Player& p);

public:
	virtual~Enemy();

	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void OnDamage() = 0;

	Position2f GetPosition();	//���݂̃|�W�V����
};

/*
//�G�̎��
�E�Z�f�b�h�}��
�E�@�g�b�v�x�r�[
�E�Z�o�b�g
�E�@�o�C�L���O�f�b�h
�E�@�E�H�[�^�[�f�b�h
�E�@�C�r���h�b�O
�E�@�m�u�[
�E�@�J���X
�E�@�W���[�J�[
�E�@�}�X�^�[�f�b�h
�E�@�I�E�@
�E�@���o�C�o���f�b�h
�E�@�W���������l(�t�@�C���[�f�b�h)
*/