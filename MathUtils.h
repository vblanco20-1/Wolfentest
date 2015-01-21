#include <math.h>
#pragma once
#include "Vector2d.h"
struct AABB
{
	Vector2d Center;
	Vector2d Size;

	float Top()
	{
		return Center.y - Size.y;
	}
	float Bot()
	{
		return Center.y + Size.y;
	}
	float Left()
	{
		return Center.x - Size.x;
	}
	float Right()
	{
		return Center.x + Size.x;
	}
};

struct HitResult
{
	Vector2d HitLocation;
	Vector2d HitNormal;
};

HitResult lineIntersectionBox(Vector2d start, Vector2d end, AABB box)
{
	HitResult result;



	//hardcore as fuck maths

	//save a few function calls
	const float Top = box.Top();
	const float Down = box.Bot();
	const float Left = box.Left();
	const float Right = box.Right();

	//check with top part of box
	if (start.y <= Top && end.y >= Top || start.y <= Top && end.y >= Top)
	{

		//now calculate the X
		Vector2d diff = end - start;

		float dist = (Top - start.y) / diff.y;
		float x = start.x + dist*diff.x;

		if (x < Right&& x > Left) // check if x is in the segment
		{
			result.HitLocation.x = x;
			result.HitLocation.y = Top;
			result.HitNormal = Vector2d(0, -1);
			return result;
		}

	}

	//check with bottom of the box 
	if (end.y <= Down && start.y >= Down || end.y < Down && start.y >= Down)
	{



		//now calculate the X
		Vector2d diff = end - start;

		float dist = (Down - start.y) / diff.y;
		float x = start.x + dist*diff.x;

		if (x < Right && x > Left) // check if x is in the segment
		{
			result.HitLocation.x = x;
			result.HitLocation.y = Down;
			result.HitNormal = Vector2d(0, +1);
			return result;
		}

	}
	//check the right of the box
	if (end.x <= Right && start.x >= Right || end.x <= Right && start.x >= Right)
	{


		//now calculate the Y
		Vector2d diff = end - start;

		float dist = (Right - start.x) / diff.x;
		float y = start.y + dist*diff.y;

		if (y < Down && y > Top) // check if x is in the segment
		{
			result.HitLocation.y = y;
			result.HitLocation.x = Right;
			result.HitNormal = Vector2d(1, 0);
			return result;
		}

	}


	//check the left of the box
	if (start.x <= Left && end.x >= Left || start.x <= Left && end.x >= Left)
	{

		//now calculate the Y
		Vector2d diff = end - start;

		float dist = (Left - start.x) / diff.x;
		float y = start.y + dist*diff.y;

		if (y < Down && y > Top) // check if x is in the segment
		{
			result.HitLocation.y = y;
			result.HitLocation.x = Left;
			result.HitNormal = Vector2d(-1, 0);
			return result;
		}

	}
	//return default trash result at 0
	return result;
}