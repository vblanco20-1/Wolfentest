#include "Vector2d.h"




void Vector2d::rotate(float angle)
{
	Vector2d newVec;

	float px = x;
	float py = y;
	if (angle > 0)
	{
		this->x = px*cos(angle) - py*sin(angle);
		this->y = px*sin(angle) + py*cos(angle);
	}
	else
	{
		this->x =px*cos(-angle) + py*sin(-angle);
		this->y = -px*sin(-angle) + py*cos(-angle);
	}


	/*float ang = atanf(this->x / this->y);
	float size = this->size();

	this->y = cosf(angle+ang)*size;
	
	this->x = sinf(angle+ang)*size;*/
	
}

float Vector2d::size()
{
	return VSize(*this);
}

float VSize(Vector2d& vec)
{
	return sqrt(vec.x * vec.x + vec.y * vec.y);
}

