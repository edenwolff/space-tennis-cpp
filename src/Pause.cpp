#include "header.h"
#include "Pause.h"

void Pause::initialiseState()
{
	engine->lockBackgroundForDrawing();
	pauseBackground.renderImage(engine->getBackgroundSurface(), 0, 0, 0, 0, pauseBackground.getWidth(), pauseBackground.getHeight());
	engine->unlockBackgroundForDrawing();
}

void Pause::setupButtons()
{
	engine->lockForegroundForDrawing();

	engine->drawForegroundRectangle(500, 150, 700, 200, 0x0000FF);
	engine->drawForegroundString(550, 160, "RESUME", 0xFFFFFF, NULL);

	engine->drawForegroundRectangle(450, 250, 750, 300, 0x0000FF);
	engine->drawForegroundString(470, 260, "RETURN TO MENU", 0xFFFFFF, NULL);

	engine->unlockForegroundForDrawing();
}