#pragma once
#include "peripheral.h"

//�V�[���Ǘ��̃N���X
//�������z�N���X
class Scene
{
public:
	Scene();
	virtual ~Scene();

	virtual void Update(peripheral& p) = 0;
};
