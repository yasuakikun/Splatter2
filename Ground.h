#pragma once
#include "Geometry.h"

//�n�ʂ̃N���X
//�t�@�C���Ȃǂ���n�ʂ�ǂݍ���Ō��݂̒n�ʂ̍�����Ԃ�
class Ground
{

public:
	Ground();
	~Ground();

	//���݂̃v���C���[�ʒu�ł� 
	//�u����ׂ��n�ʁv�̍�����Ԃ��B 
	int GetCurrentGroundY(Position2f& pos)const;
};
