#include "CollisionDetector.h"

CollisionDetector::CollisionDetector()
{
}

CollisionDetector::~CollisionDetector()
{
}

bool CollisionDetector::isCollided(const Rect rc1, const Rect rc2)
{
	return abs(rc1.center.x - rc2.center.x) < (rc1.Wigth()  + rc2.Wigth() ) / 2
		&& abs(rc1.center.y - rc2.center.y) < (rc1.Height() + rc2.Height()) / 2;
}
