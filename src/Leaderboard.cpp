#include "header.h"
#include "Leaderboard.h"

void Leaderboard::initialiseState()
{
	engine->lockForegroundForDrawing();
	background.renderImage(engine->getForegroundSurface(), 0, 0, 0, 0, background.getWidth(), background.getHeight());
	engine->drawForegroundString(20, 20, "PRESS Q TO RETURN", 0xFFFFFF, NULL);
	engine->drawForegroundString(20, 400, "USE ARROW KEYS TO SCROLL AND MOUSE WHEEL TO ZOOM", 0xFFFFFF, NULL);
	engine->drawForegroundString(20, 450, "(PRESS ESC TO RESET SCROLL)", 0xFFFFFF, NULL);
	engine->unlockForegroundForDrawing();
}