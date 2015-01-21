#pragma once
#include <math.h>
struct Vector2d
{
	float x;
	float y;
	Vector2d() :x(0), y(0){	}
	Vector2d(float X, float Y) :x(X), y(Y){}

	Vector2d operator+(Vector2d &other) const
	{
		Vector2d res = *this;
		res.x += other.x;
		res.y += other.y;
		return res;
	}
	Vector2d operator-(Vector2d &other) const
	{
		Vector2d res = *this;
		res.x -= other.x;
		res.y -= other.y;
		return res;
	}
	Vector2d operator*(float other)const
	{
		Vector2d res = *this;
		res.x *= other;
		res.y *= other;
		return res;
	}

	void rotate(float angle);
	float size();
};
float VSize(Vector2d& vec);
