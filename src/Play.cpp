#include "header.h"
#include "Play.h"

/* Setup play state - render new background image */
void Play::initialiseState()
{
	engine->lockBackgroundForDrawing();
	gameTheme.renderImage(engine->getBackgroundSurface(), 0, 0, 0, 0, gameTheme.getWidth(), gameTheme.getHeight());
	engine->unlockBackgroundForDrawing();

	engine->setAllObjectsVisible(true);

	//rock->setVisible(false);
	engine->redrawDisplay();
}

void Play::updateState(int playerScore)
{
	char scoreBuf[128];
	sprintf(scoreBuf, "SCORE: %d", ballObject->playerScore);
	engine->lockForegroundForDrawing();
	engine->drawForegroundOval(1060, 60, 1140, 140, 0xFFFF00);
	engine->drawForegroundThickLine(1090, 82, 1090, 112, 0x0, 10);
	engine->drawForegroundThickLine(1110, 82, 1110, 112, 0x0, 10);
	engine->drawForegroundString(10, 20, scoreBuf, 0x00FF00, NULL);
	engine->unlockForegroundForDrawing();
}


