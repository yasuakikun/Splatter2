#pragma once
#include "Geometry.h"

class CollisionDetector
{
public:
	CollisionDetector();
	~CollisionDetector();

	static bool isCollided(const Rect rc1, const Rect rc2);
};

