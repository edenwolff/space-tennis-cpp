#include "header.h"
#include "Menu.h"
#include "ImageManager.h"

void Menu::initialiseState()
{
	engine->lockForegroundForDrawing();

	engine->drawForegroundRectangle(500, 150, 700, 200, 0x0000FF);
	engine->drawForegroundString(564, 160, "PLAY", 0xFFFFFF, NULL);

	engine->drawForegroundRectangle(450, 250, 750, 300, 0x0000FF);
	engine->drawForegroundString(492, 260, "LEADERBOARD", 0xFFFFFF, NULL);

	engine->drawForegroundString(890, 150, "CHOOSE SKIN:", 0xFFFFFF, NULL);

	engine->tileManager->setTopLeftPositionOnScreen(900, 200);

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			engine->tileManager->setAndRedrawMapValueAt(i, j, i*j, engine, engine->getForegroundSurface());
		}
	}

	engine->drawForegroundRectangle(500, 350, 700, 400, 0x0000FF);
	engine->drawForegroundString(564, 360, "QUIT", 0xFFFFFF, NULL);

	engine->unlockForegroundForDrawing();

}
