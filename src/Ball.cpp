#include "header.h"
#include "Ball.h"
#include "Racket.h"
#include "UtilCollisionDetection.h"

int ballNum = 1;

void Ball::virtDraw()
{
	DrawingSurface* foreground = getEngine()->getForegroundSurface();
	if (isVisible())
	{
		objectImage.renderImageApplyingMapping(getEngine(), foreground, m_iCurrentScreenX + m_iStartDrawPosX, m_iCurrentScreenY + m_iStartDrawPosY, objectImage.getWidth(), objectImage.getHeight(), &oMapper);
	}
}

void Ball::virtDoUpdate(int time)
{
	if(isVisible())
	{
		detectCollision();

		setX(getX() + getSpeedX());
		setY(getY() + getSpeedY());

		redrawDisplay();

		if (!isAlive())
		{
			setSpeedX(0);
			setSpeedY(0);

			redrawDisplay();

			getEngine()->pause();

			((Psyew3Engine*)getEngine())->finishGame();
		}

	}
}

void Ball::detectCollision()
{
	if (getX() < 0)
	{
		setSpeedX(getSpeedX() * -1);
	}
	if (getY() < 0)
	{
		setSpeedY(getSpeedY() * -1);
	}
	if (getX() >= getEngine()->getWindowWidth() - getWidth())
	{
		setSpeedX(getSpeedX() * -1);
	}

	Racket* pObject = (Racket*)getEngine()->getDisplayableObject(0);

	if (checkCollision((GameObject)*pObject))
	{
		if (speedY > 0) 
		{
			setSpeedY(getSpeedY() * -1);
			playerScore += 10;
		}

		if (ballNum == 0)
		{
			objectImage = selectedBall;
			ballNum = 1;
		}

		else
		{
			objectImage = oBall;
			ballNum = 0;
		}
	}


}

bool Ball::isAlive()
{
	if (getY() >= getEngine()->getWindowHeight() - getHeight())
	{
		return false;
	}
	return true;
}

void Ball::resetObject()
{
	playerScore = 0;
	setX(300);
	setY(100);
	setSpeedX(10);
	setSpeedY(10);
}
