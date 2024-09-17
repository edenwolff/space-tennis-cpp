#include "header.h"
#include "GameObject.h"
#include "UtilCollisionDetection.h"

void GameObject::resetObject(){}

inline int max(int a, int b)
{
	if (a > b)
		return a;
	return b;
}

inline int min(int a, int b)
{
	if (a < b)
		return a;
	return b;
}

bool GameObject::checkCollision(GameObject o2)
{
	if (CollisionDetection::checkRectangles(getX(), getX() + getWidth(), getY(), getY() + getHeight(),
		o2.getX(), o2.getX() + o2.getWidth(), o2.getY(), o2.getY() + o2.getHeight()))
	{
		// Forming overlap rectangle
		int topLeftCornerX = max(getX(), o2.getX());
		int topleftCornerY = max(getY(), o2.getY());
		int topRightCornerX = min(getX() + getWidth(), o2.getX() + o2.getWidth());
		int bottomLeftCornerY = min(getY() + getHeight(), o2.getY() + o2.getHeight());

		for (int x = topLeftCornerX; x <= topRightCornerX; x++)
		{
			for (int y = topleftCornerY; y <= bottomLeftCornerY; y++)
			{
				if (getEngine()->rawGetForegroundPixel(x, y) != oMapper.getTransparencyColour())
				{
					return true;
				}
			}
		}

	}

	// No collision
	return false;
}

