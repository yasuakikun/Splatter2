#pragma once
#include "peripheral.h"

//シーン管理のクラス
//純粋仮想クラス
class Scene
{
public:
	Scene();
	virtual ~Scene();

	virtual void Update(peripheral& p) = 0;
};
