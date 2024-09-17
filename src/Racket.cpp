#include "header.h"
#include "Racket.h"
#include "ImagePixelMapping.h"

void Racket::virtDraw()
{
	DrawingSurface* foreground = getEngine()->getForegroundSurface();
	if (isVisible())
	{
		if (right)
		{
			oMapper.setRotation(-M_PI / 2);
			objectImage.renderImageApplyingMapping(getEngine(), foreground, getX() + m_iStartDrawPosX, getY() + m_iStartDrawPosY, objectImage.getWidth(), objectImage.getHeight(), &oMapper);
		}
		else
		{
			oMapper.setRotation(M_PI / 2);
			objectImage.renderImageApplyingMapping(getEngine(), foreground, getX() + m_iStartDrawPosX, getY() + m_iStartDrawPosY, objectImage.getWidth(), objectImage.getHeight(), &oMapper);
		}
	}
}

void Racket::virtDoUpdate(int)
{
	if (isVisible())
	{
		if (getEngine()->isKeyPressed(SDLK_RIGHT))
		{
			right = true;
			setX(getX() + 10);
		}
		if (getEngine()->isKeyPressed(SDLK_LEFT))
		{
			right = false;
			setX(getX() - 10);
		}

		detectCollision();

		redrawDisplay();
	}
}

void Racket::detectCollision()
{
	if (getX() < 0)
	{
		setX(0);
	}

	if (getX() >= getEngine()->getWindowWidth() - getWidth())
	{
		setX(getEngine()->getWindowWidth() - getWidth());
	}
}

void Racket::resetObject()
{
	setX(600);
}
