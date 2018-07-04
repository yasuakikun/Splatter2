#pragma once
#include "Scene.h"

class GameContinueScene :
	public Scene
{
private:
	int continueCntImg;
	int frame;

	Game& game;

public:
	GameContinueScene();
	~GameContinueScene();

	void Update(peripheral& p);
};

