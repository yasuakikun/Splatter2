#pragma once
#include "Scene.h"
#include <memory>

class Game;
class Stage;
class Camera;
class BackGronud;
class Player;
class Ground;
class EnemyFactory;

class GamePlayingScene :
	public Scene
{
private:
	Game & game;
	std::shared_ptr<Stage> stage;
	std::shared_ptr<Camera> camera;
	std::shared_ptr<BackGronud> bk;
	std::shared_ptr<Player> pl;
	std::shared_ptr<Ground> g;
	std::shared_ptr<EnemyFactory> factory;

	int fadeTimer;	//フェード中タイマー

	void (GamePlayingScene::*updater)();

	void FadeinUpdate();
	void NormalUpdate();
	void FadeoutUpdate();

public:
	GamePlayingScene();
	~GamePlayingScene();

	void Update(peripheral& p);
};
