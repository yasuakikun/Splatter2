#pragma once

//ゲージ類の制御、表示
class HUD
{
private:
	int barTopH;//上バーのUI画像ハンドル 
	int barBottomH;//下バーのUI画像ハンドル 
	const Player& _player;//プレイヤーへの参照 
	int _score;//スコア

public:
	HUD(const Player& player);
	~HUD();

	///更新
	void Update();

	///描画 
	void Draw();
};
