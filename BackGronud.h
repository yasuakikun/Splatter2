#pragma once

class Camera;

class BackGronud
{
public:
	BackGronud(Camera& _camera);
	~BackGronud();

	//void Update();
	void Draw();
private:
	int bg_hundle;
	int bg_turn_hundle;

	int bar_bottom;
	int bar_top;

	//int blood         = DxLib::LoadGraph("img/blood.png");
	//int bloodsplash   = DxLib::LoadGraph("img/bloodsplash.png");

	Camera& camera;
};


