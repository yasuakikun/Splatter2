#pragma once
#include <memory>

//型が確定していない使い勝手の良いstructになる
template <typename T>
struct Vector2D
{
	Vector2D() : x(0), y(0) {}
	Vector2D(T inx, T iny) : x(inx), y(iny) {}
	T x;
	T y;

	void operator+=(const Vector2D<T>& in)
	{
		x += in.x;
		y += in.y;
	}

	void operator-=(const Vector2D<T>& in)
	{
		x -= in.x;
		y -= in.y;
	}
};

typedef Vector2D<int> Vector2;
typedef Vector2 Position2;

typedef Vector2D<float> Vector2f;
typedef Vector2f Position2f;

struct Size
{
	Size() {}
	Size(int x, int y) : w(x), h(y) {}
	int w;
	int h;
};

//Vector2Dのためのオペレーターオーバーロード
template <typename T>
Vector2D<T> operator+(const Vector2D<T>& lv, const Vector2D<T>& rv)
{
	return Vector2D<T>(lv.x + rv.x, lv.y + rv.y);
}

template <typename T>
Vector2D<T> operator -(const Vector2D<T>& lv, const Vector2D<T>& rv)
{
	return Vector2D<T>(lv.x + rv.x, lv.y + rv.y);
}

//矩形の構造体
struct Rect {
	Rect() : center(0, 0), size(0, 0) {}
	Rect(int x, int y, int w, int h) : center(x, y), size(w, h) {}
	Rect(Position2& inpos, int inw, int inh) : center(inpos), size(inw, inh) {}

	Position2 center;
	Size size;
	const int Left() const;
	const int Top()const;
	const int Right()const;
	const int Bottom()const;
	const int Wigth()const;
	const int Height()const;

	//矩形の描画
	void Draw(unsigned int color = 0xffffffff);

	void Draw(const Vector2& offset, unsigned int color = 0xffffffff);
};

class Geometry
{
public:
	Geometry();
	~Geometry();
};

//コメントは、基本的にヘッダ側に書く