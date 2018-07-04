#pragma once
#include "Scene.h"
#include <memory>

struct ScreenSize {
	int w;
	int h;
};

class Game
{
private:
	//�V���O���g���p�^�[��
	Game();	//�쐬�֎~
	Game(const Game& g) {};	//�R�s�[�֎~
	void operator= (const Game&) {};	//����֎~

										//�V�[���Ǘ��|�C���^
	std::shared_ptr<Scene> scene;

	ScreenSize size;

public:
	static Game& Instance()
	{
		static Game instance;
		return instance;
	}
	~Game();

	//�������n
	void Initalize();

	//�Q�[����(���̊֐����Q�[�����N��)
	void Run();

	//�㏈��
	void Terminent();

	//�X�N���[���̃T�C�Y��Ԃ�
	const ScreenSize& GetScreenSize();

	//�L�����̊g�嗦
	float GetObjectScale();

	//�V�[���؂�ւ�
	void ChangeScene(Scene* newScene);
};
