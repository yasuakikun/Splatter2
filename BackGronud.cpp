#include "Camera.h"
#include "BackGronud.h"
#include <DxLib.h>

const Vector2 bg_size = { 576, 488 };

BackGronud::BackGronud(Camera& _camera) : camera(_camera)
{
	bg_hundle = DxLib::LoadGraph("img/bg.png");
	bg_turn_hundle = bg_hundle;

	bar_top = DxLib::LoadGraph("img/bar_top.png");
	bar_bottom = DxLib::LoadGraph("img/bar_bottom.png");
}

BackGronud::~BackGronud()
{
}

//void BackGronud::Update()
//{
//
//}

void BackGronud::Draw()
{
	auto scroll = camera.GetViewport().Left();	//左端スクロール値算出
	scroll %= 1152;
	DrawRotaGraph(0 - scroll, 216, 1.0f, 0.0f, bg_hundle, false, true);
	DrawRotaGraph(576 - scroll, 216, 1.0f, 0.0f, bg_turn_hundle, false);

	DrawRotaGraph(1152 - scroll, 216, 1.0f, 0.0f, bg_hundle, false, true);
	DrawRotaGraph(1152 + 576 - scroll, 216, 1.0f, 0.0f, bg_turn_hundle, false);

	//バナーの描画
	DxLib::DrawGraph(0, 0, bar_top, true);
	DxLib::DrawGraph(0, 448 - 64, bar_bottom, true);
}
