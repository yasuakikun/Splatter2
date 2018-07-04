#pragma once

//周辺機器(キーボード、パッド等)
class peripheral
{
public:
	peripheral();
	~peripheral();

	//入力情報の更新(毎フレームコールしてください) 
	//@attension
	void Update();

	//現在の押下状態の検出 
	//@param key_button 調べたいボタンID 
	//@retval true 押してる 
	//@retval false 押してない 
	const bool IsPressing(int key_button)const;

	//現在のトリガー状態(押した瞬間)の検出 
	//@param key_button 調べたいボタンID 
	//@retval true 押してる
	//@retval false 押してない 
	const bool IsTrigger(int key_button)const;

private:
	int padState;		//現在の入力状態 
	int lastPadState;	//直前の入力状態
};
