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
	//シングルトンパターン
	Game();	//作成禁止
	Game(const Game& g) {};	//コピー禁止
	void operator= (const Game&) {};	//代入禁止

										//シーン管理ポインタ
	std::shared_ptr<Scene> scene;

	ScreenSize size;

public:
	static Game& Instance()
	{
		static Game instance;
		return instance;
	}
	~Game();

	//初期化系
	void Initalize();

	//ゲーム中(この関数中ゲームが起動)
	void Run();

	//後処理
	void Terminent();

	//スクリーンのサイズを返す
	const ScreenSize& GetScreenSize();

	//キャラの拡大率
	float GetObjectScale();

	//シーン切り替え
	void ChangeScene(Scene* newScene);
};
