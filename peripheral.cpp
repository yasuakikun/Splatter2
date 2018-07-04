#include "peripheral.h"
#include<DxLib.h>

peripheral::peripheral() : lastPadState(0), padState(0)
{
}

peripheral::~peripheral()
{
}

//���݂̉�����Ԃ̌��o
const bool peripheral::IsPressing(int keyButton) const
{
	return padState & keyButton;
}

//���݂̃g���K�[���(�������u��)�̌��o
const bool peripheral::IsTrigger(int keyButton) const
{
	return ((lastPadState & padState) ^ padState) & keyButton;
}

void peripheral::Update()
{
	lastPadState = padState;
	padState = DxLib::GetJoypadInputState(DX_INPUT_KEY_PAD1);
}
