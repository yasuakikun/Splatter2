#pragma once

//�Q�[�W�ނ̐���A�\��
class HUD
{
private:
	int barTopH;//��o�[��UI�摜�n���h�� 
	int barBottomH;//���o�[��UI�摜�n���h�� 
	const Player& _player;//�v���C���[�ւ̎Q�� 
	int _score;//�X�R�A

public:
	HUD(const Player& player);
	~HUD();

	///�X�V
	void Update();

	///�`�� 
	void Draw();
};
