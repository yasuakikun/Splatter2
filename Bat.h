#pragma once
#include "Enemy.h"

class Camera;
class Player;
class EnemyFactory;

class Bat :
	public Enemy
{
private:
	int weitTimer;	//�_���[�W����

	Camera& camera;
	const Player& player;

	//�_���[�W���󂯂��ꍇ
	void OnDamage();

	//�����_�����
	void Neutral();	//�j���[�g����
	void Fly();		//���

					//�����o�֐��|�C���^(�����_��)
	void (Bat::*updater)();	//�A�b�v�f�[�^

							//���(�X�e�[�g)�ɂ�����֐�
							//�j���[�g����
	void NeutralUpdate();

	//���
	void FlyUpdate();

	//���S
	void DieUpdate();

	friend EnemyFactory;
	//�V���O���g��
	Bat(const Player& _player, Camera& _camera);
	Bat(const Bat& b);
	void operator= (const Bat& b);

public:
	~Bat();

	void Update();
	void Draw();

	Enemy* Clone();
};
