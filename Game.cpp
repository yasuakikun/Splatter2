#include "TitleScene.h"
#include "GamePlayingScene.h"
#include "GameOverScene.h"
#include "Geometry.h"
#include "peripheral.h"
#include "Game.h"
#include "TitleScene.h"
#include "GamePlayingScene.h"
#include "GameOverScene.h"
#include "Geometry.h"
#include "peripheral.h"
#include "Game.h"
#include <DxLib.h>

const Vector2 screensize = { 768, 448 };

Game::Game()
{
	size.w = screensize.x;
	size.h = screensize.y;
}

Game::~Game()
{
}

void Game::Initalize()
{
	DxLib::SetGraphMode(size.w, size.h, 32);
	DxLib::ChangeWindowMode(true);
	DxLib::SetWindowText("SplatterHouse 1601287_����_����");
	if (DxLib::DxLib_Init() == -1)
	{
		return;
	}
	SetDrawScreen(DX_SCREEN_BACK);

	ChangeScene(new TitleScene);
}

void Game::Run()
{
	peripheral Peripheral;

	while (DxLib::ProcessMessage() == 0)
	{
		if (CheckHitKey(KEY_INPUT_ESCAPE))
		{
			break;
		}

		DxLib::ClsDrawScreen();

		//�L�[���̓A�b�v�f�[�g
		Peripheral.Update();

		//�V�[���A�b�v�f�[�g
		scene->Update(Peripheral);

		DxLib::ScreenFlip();
	}
}

void Game::Terminent()
{
	DxLib::DxLib_End();
}

const ScreenSize& Game::GetScreenSize()
{
	return size;
}

float Game::GetObjectScale()
{
	return 2.0f;	//�Ƃ肠�����Œ�l
}

void Game::ChangeScene(Scene* newScene)
{
	scene.reset(newScene);
}

//����������ƃ����[�X�ł͎��s����Ȃ�
//#ifdef _DEBUG
//#endif 