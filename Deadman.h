#pragma once
#include "Enemy.h"

class Camera;
class Player;
class EnemyFactory;

class Deadman :
	public Enemy
{
private:
	int weitTimer;	//�_���[�W����

	Camera& camera;
	const Player& player;

	//�����_���֑��
	void Neutral();	//�j���[�g����
	void Walk();	//����
	void OnDamage();//�_���[�W
	void Die();		//���S

					//�����o�֐��|�C���^(�����_��)
	void (Deadman::*updater)();	//�A�b�v�f�[�^

								//���(�X�e�[�g)�ɂ�����֐�
								//�j���[�g����
	void NeutralUpdate();

	//����
	void WalkUpdate();

	//�_���[�W��
	void DamageUpdate();

	//���S
	void DieUpdate();

	friend EnemyFactory;
	//�V���O���g��
	Deadman(const Player& _player, Camera& _camera);
	Deadman(const Deadman& d);
	void operator= (const Deadman& d);

public:
	~Deadman();

	void Update();
	void Draw();

	Enemy* Clone();
};
