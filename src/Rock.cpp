#include "header.h"
#include "Rock.h"
#include "Racket.h"

void Rock::virtDraw()
{
	if (isVisible())
	{
		DrawingSurface* foreground = getEngine()->getForegroundSurface();
		objectImage.renderImageApplyingMapping(getEngine(), foreground, getX(), getY(), objectImage.getWidth(), objectImage.getHeight(), &oMapper);
	}
}
void Rock::virtDoUpdate(int time)
{
	if (time >= tickOffset + 10)
	{
		calculatePath();

		if (getY() > 0 && getY() < 50)
		{
			objectImage = ImageManager::get()->getImagebyURL("rock.png", true, true);
		}

		else if (getY() > 50 && getY() < 100)
		{
			objectImage = ImageManager::get()->getImagebyURL("fire1.png", true, true);
		}

		else if (getY() > 150 && getY() < 200)
		{
			objectImage = ImageManager::get()->getImagebyURL("fire2.png", true, true);
		}

		else if (getY() > 200 && getY() < 250)
		{
			objectImage = ImageManager::get()->getImagebyURL("fire3.png", true, true);
		}

		else if (getY() > 250 && getY() < 300)
		{
			objectImage = ImageManager::get()->getImagebyURL("fire4.png", true, true);
		}

		else if (getY() > 300 && getY() < 350)
		{
			objectImage = ImageManager::get()->getImagebyURL("fire5.png", true, true);
		}

		if (getY() >= getEngine()->getWindowHeight())
		{
			resetObject();

			// Remove rock from array after it has disappeared
			getEngine()->removeDisplayableObject(this);
			getEngine()->drawableObjectsChanged();

			// Re-spawn rock
			((Psyew3Engine*)getEngine())->respawnRock();
		}

		Racket* pObject = (Racket*)getEngine()->getDisplayableObject(0);

		if (pObject->isVisible())
		{
			if (checkCollision(*pObject))
			{
				((Psyew3Engine*)getEngine())->finishGame();
			}
		}
	}

	tickOffset = time;
	redrawDisplay();

}


void Rock::resetObject()
{
	setY(0);
	setX(600);

	setSpeedX(5);
	setSpeedY(5);

	objectImage = ImageManager::get()->getImagebyURL("rock.png", true, true);
}

void Rock::calculatePath()
{
	if (((GameObject*)getEngine()->getDisplayableObject(0))->getY() < getY())
	{
		setSpeedY(15);
		setY(getY() + getSpeedY());
	}

	else if (((GameObject*)getEngine()->getDisplayableObject(0))->getY() - getY() <= 200)
	{
		setSpeedX(0);
		setY(getY() + getSpeedY());
	}

	else
	{
		setX(((GameObject*)getEngine()->getDisplayableObject(0))->getX() - 50);

		setY(getY() + getSpeedY());
	}
}
