#pragma once

//���Ӌ@��(�L�[�{�[�h�A�p�b�h��)
class peripheral
{
public:
	peripheral();
	~peripheral();

	//���͏��̍X�V(���t���[���R�[�����Ă�������) 
	//@attension
	void Update();

	//���݂̉�����Ԃ̌��o 
	//@param key_button ���ׂ����{�^��ID 
	//@retval true �����Ă� 
	//@retval false �����ĂȂ� 
	const bool IsPressing(int key_button)const;

	//���݂̃g���K�[���(�������u��)�̌��o 
	//@param key_button ���ׂ����{�^��ID 
	//@retval true �����Ă�
	//@retval false �����ĂȂ� 
	const bool IsTrigger(int key_button)const;

private:
	int padState;		//���݂̓��͏�� 
	int lastPadState;	//���O�̓��͏��
};
