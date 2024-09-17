 #include "header.h"
#include "End.h"
#include <vector>

using namespace std;

void End::initialiseState()
{
	/* Clear displayable array contents without deleting objects */
	//engine->drawableObjectsChanged();
	//engine->destroyOldObjects(false);

	char scoreBuf[128];
	sprintf(scoreBuf, "GAME OVER, YOUR SCORE: %d", finalScore);

	engine->lockForegroundForDrawing();
	engine->drawForegroundString(420, 50, scoreBuf, 0xFFFFFF, NULL);
	engine->drawForegroundString(450, 120, "ENTER NAME:", 0xFFFFFF, NULL);

	engine->drawForegroundRectangle(300, 250, 650, 300, 0x0000FF);
	engine->drawForegroundString(350, 260, "RETURN TO MENU", 0xFFFFFF, NULL);

	engine->drawForegroundRectangle(700, 250, 1100, 300, 0x0000FF);
	engine->drawForegroundString(740, 260, "ADD TO LEADERBOARD", 0xFFFFFF, NULL);

	engine->unlockForegroundForDrawing();

	engine->redrawDisplay();
}

void End::setScore(int score)
{
	finalScore = score;
}

void End::scanInput(int iKeyCode)
{
	if (inputBuf.size() < 9)
	{
		if (iKeyCode >= 97 && iKeyCode <= 122)
		{
			inputBuf.push_back(iKeyCode);
		}
	}

	if (iKeyCode == 8)
	{
		if (inputBuf.size() != 0)
		{
			inputBuf.pop_back();
		}
	}
}

void End::printName()
{
	char buffer[16]{};
	for (int i = 0; i < inputBuf.size(); i++)
	{
		buffer[i] = inputBuf.at(i);
	}

	if (inputBuf.size() != 0)
	{
		engine->lockForegroundForDrawing();
		engine->drawForegroundString(650, 120, buffer, 0xFFFFFF, NULL);
		engine->unlockForegroundForDrawing();
	}
}
