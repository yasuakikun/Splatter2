#include "peripheral.h"
#include<DxLib.h>

peripheral::peripheral() : lastPadState(0), padState(0)
{
}

peripheral::~peripheral()
{
}

//現在の押下状態の検出
const bool peripheral::IsPressing(int keyButton) const
{
	return padState & keyButton;
}

//現在のトリガー状態(押した瞬間)の検出
const bool peripheral::IsTrigger(int keyButton) const
{
	return ((lastPadState & padState) ^ padState) & keyButton;
}

void peripheral::Update()
{
	lastPadState = padState;
	padState = DxLib::GetJoypadInputState(DX_INPUT_KEY_PAD1);
}
