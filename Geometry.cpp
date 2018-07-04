#include "Geometry.h"
#include "Dxlib.h"

Geometry::Geometry()
{
}

Geometry::~Geometry()
{
}

const int Rect::Left() const
{ 
	return (center.x - size.w / 2); 
}
const int Rect::Top() const
{
	return (center.y - size.h / 2);
}
const int Rect::Right() const
{ 
	return (center.x + size.w / 2); 
}
const int Rect::Bottom() const
{ 
	return (center.y + size.h / 2); 
}

const int Rect::Wigth() const
{
	return size.w;
}

const int Rect::Height() const
{
	return size.h;
}

void Rect::Draw(unsigned int color)
{
	DxLib::DrawBox(Left(), Top(), Right(), Bottom(), 0xffffff, false);
}

void Rect::Draw(const Vector2 & offset, unsigned int color)
{
	DxLib::DrawBox(Left() + offset.x, Top() + offset.y, Right() + offset.x, Bottom() + offset.y, 0xffffff, false);
}
