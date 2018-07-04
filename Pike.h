#pragma once
#include "Enemy.h"

class Camera;
class Player;
class EnemyFactory;

class Pike :
	public Enemy
{
private:
	int weitTimer;	//���̍U���܂ł̑҂�����

	Camera& camera;
	const Player& player;

	//�����_���֑��
	void Neutral();	//�j���[�g����
	void Attack();	//�U��

	void OnDamage();//�_���[�W

	//�����o�֐��|�C���^(�����_��)
	void (Pike::*updater)();	//�A�b�v�f�[�^

	//���(�X�e�[�g)�ɂ�����֐�
	//�j���[�g����
	void NeutralUpdate();

	//�U��
	void AttackUpdate();

	friend EnemyFactory;
	//�V���O���g��
	Pike(const Player& _player, Camera& _camera);
	Pike(const Pike& pike);
	void operator= (const Pike& pike);

public:
	~Pike();

	void Update();
	void Draw();

	Enemy* Clone();
};
