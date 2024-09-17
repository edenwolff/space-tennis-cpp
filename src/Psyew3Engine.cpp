#include "header.h"
#include "Psyew3Engine.h"
#include "Psyew3TileManager.h"
#include "ImageManager.h"
#include "State.h"
#include "Menu.h"
#include "Play.h"
#include "Ball.h"
#include "Pause.h"
#include "End.h"
#include "Leaderboard.h"
#include <fstream>
#include <iostream>
using namespace std;

char firstLine[16];
char secondLine[16];
char thirdLine[16];
char fourthLine[16];
char fifthLine[16];

int in, out;

Menu* startUpState;
Play* gameState;
Leaderboard* leaderboardState;
Pause* pauseState;
End* endState;

struct GameResult {
	string name;
	int score;
};

int Psyew3Engine::virtInitialise()
{
	pause();
	getBackgroundSurface()->setDrawPointsFilter(&m_filterTranslation);
	getForegroundSurface()->setDrawPointsFilter(&m_filterTranslation);
	return BaseEngine::virtInitialise();
}

void Psyew3Engine::virtSetupBackgroundBuffer()
{
	SimpleImage menuBackground = ImageManager::loadImage("space_background.png", true);
	menuBackground.renderImage(getBackgroundSurface(), 0, 0, 0, 0,
	menuBackground.getWidth(), menuBackground.getHeight());
	if (startUpState == NULL)
	{
		startUpState = new Menu(this);
	}

	currentState = startUpState;
}

void Psyew3Engine::virtMouseWheel(int x, int y, int which, int timestamp)
{
	if (currentState == leaderboardState)
	{
		// We grab the position of the centre of the screen before the zoom
		int iOldCentreX = convertClickedToVirtualPixelXPosition(this->getWindowWidth() / 2);
		int iOldCentreY = convertClickedToVirtualPixelYPosition(this->getWindowHeight() / 2);

		if (y < 0)
		{
			m_filterScaling.compress();
			in++;
		}
		else if (y > 0)
		{
			m_filterScaling.stretch();
			out++;
		}

		// Now we grab the position after the zoom
		int iNewCentreX = convertClickedToVirtualPixelXPosition(this->getWindowWidth() / 2);
		int iNewCentreY = convertClickedToVirtualPixelYPosition(this->getWindowHeight() / 2);

		redrawDisplay();
	}
}


void Psyew3Engine::virtMouseDown(int iButton, int iX, int iY)
{
	if (currentState == startUpState)
	{
		// Play click handle
		if (iX >= 500 && iX <= 700 && iY >= 150 && iY <= 200)
		{
			currentState = gameState;
			unpause();
			currentState->initialiseState();

	
			resetAllObjects();
		}

		//Leaderboard click handle
		if (iX >= 450 && iX <= 750 && iY >= 250 && iY <= 300)
		{
			currentState = leaderboardState;
		}


		// Quit button
		if (iX >= 500 && iX <= 700 && iY >= 350 && iY <= 400)
		{
			setExitWithCode(0);
		}

		if (tileManager->isValidTilePosition(iX, iY))
		{
			if (tileManager->getMapXForScreenX(iX) == 0 && tileManager->getMapYForScreenY(iY) == 0)
			{
				tileManager->racket = tileManager->selectedRacket;
				tileManager->racket2 = ImageManager::get()->getImagebyURL("racket2.png", true, true);

				gameState->racket->objectImage = ImageManager::get()->getImagebyURL("racket1.png", true, true);
			}

			else if (tileManager->getMapXForScreenX(iX) == 0 && tileManager->getMapYForScreenY(iY) == 1)
			{
				tileManager->racket2 = tileManager->selectedRacket2;
				tileManager->racket = ImageManager::get()->getImagebyURL("racket1.png", true, true);

				gameState->racket->objectImage = ImageManager::get()->getImagebyURL("racket2.png", true, true);
			}

			else if (tileManager->getMapXForScreenX(iX) == 1 && tileManager->getMapYForScreenY(iY) == 0)
			{
				tileManager->ballSkin = tileManager->selectedball1;
				tileManager->orangeBallSkin = ImageManager::get()->getImagebyURL("ball2_skin.png", true, true);

				gameState->ballObject->selectedBall = ImageManager::get()->getImagebyURL("tennis_ball.png", true, true);
				gameState->ballObject->objectImage = gameState->ballObject->selectedBall;
			}

			else
			{
				tileManager->orangeBallSkin = tileManager->selectedball2;
				tileManager->ballSkin = ImageManager::get()->getImagebyURL("skin_ball.png", true, true);

				gameState->ballObject->selectedBall = ImageManager::get()->getImagebyURL("orange_ball.png", true, true);
				gameState->ballObject->objectImage = gameState->ballObject->selectedBall;
			}

			tileManager->drawAllTiles(this, getForegroundSurface());
			redrawDisplay();
		}
	}

	else if (currentState == gameState)
	{
		if (iX >= 1060 && iX <= 1140  && iY >= 60 && iY <= 140 )
		{
			// Set all objects invisible
			setAllObjectsVisible(false);

			currentState = pauseState;
			pause();
			currentState->initialiseState();
		}
	}


	else if(currentState == endState)
	{
		// Return to menu
		if (iX >= 300 && iX <= 650 && iY >= 250 && iY <= 300)
		{
			endState->inputBuf.clear();
			lockBackgroundForDrawing();
			virtSetupBackgroundBuffer();
			unlockBackgroundForDrawing();

			currentState = startUpState;

			redrawDisplay();
		}

		else if (iX>=700 && iX<=1100 && iY>=250 && iY<=300)
		{
			GameResult recentGame;
			// copy entered name
			for (int i = 0; i < endState->inputBuf.size(); i++)
			{
				recentGame.name += endState->inputBuf[i];
			}

			recentGame.score = playerScore;

			//write to file
			ofstream highScoreFile("file.csv", ios::app | ios::out);

			highScoreFile << recentGame.name + ", ";
			highScoreFile << recentGame.score;

			highScoreFile << endl;
			highScoreFile.close();

			endState->inputBuf.clear();
			lockBackgroundForDrawing();
			virtSetupBackgroundBuffer();
			unlockBackgroundForDrawing();

			currentState = startUpState;

			redrawDisplay();
		}
	}

	else if (currentState == pauseState)
	{
		if (iX >= 500 && iX <= 700 && iY >= 150 && iY <= 200)
		{
			currentState = gameState;
			unpause();
			currentState->initialiseState();
		}

		else if (iX >= 450 && iX <= 750 && iY >= 250 && iY <= 300)
		{
			resetAllObjects();
			lockBackgroundForDrawing();
			virtSetupBackgroundBuffer();
			unlockBackgroundForDrawing();

			currentState = startUpState;
		}
	}
}

/* Create objects (only once) and store them in array */
int Psyew3Engine::virtInitialiseObjects()
{
	gameState = new Play(this);
	pauseState = new Pause(this);
	leaderboardState = new Leaderboard(this);
	endState = new End(this);

	createObjectArray(3);

	gameState->ballObject = new Ball(300, 100, 50, 50, this);
	gameState->racket = new Racket(600, 500, 100, 100, this);
	gameState->rock = new Rock(300, 0, 100, 100, this);

	tileManager = new Psyew3TileManager();

	addObjectsToArray();

	setAllObjectsVisible(false);

	return 0;
}

void Psyew3Engine::respawnRock()
{
	appendObjectToArray(gameState->rock);
	drawableObjectsChanged();
}

void Psyew3Engine::finishGame()
{
	playerScore = gameState->ballObject->playerScore;


	// Switch states
	setAllObjectsVisible(false);
	currentState = endState;
	((End*)currentState)->setScore(playerScore);
	currentState->initialiseState();
}

void Psyew3Engine::updateGame(int playerScore)
{
	((Play*)(currentState))->updateState(playerScore);
}

void Psyew3Engine::addObjectsToArray()
{
	storeObjectInArray(0, gameState->racket);
	appendObjectToArray(gameState->ballObject);
	appendObjectToArray(gameState->rock);
}

void Psyew3Engine::virtDrawStringsUnderneath()
{
	if (currentState == startUpState)
	{
		((Menu*)currentState)->initialiseState();

		drawForegroundString(500, 50, "SPACE TENNIS", 0xFFFFFF, NULL);
	}

	else if (currentState == gameState)
	{
		gameState->initialiseState();
		gameState->updateState(gameState->ballObject->playerScore);
	}

	else if (currentState == endState)
	{
		currentState->initialiseState();

		endState->printName();
	}

	else if (currentState == pauseState)
	{
		pauseState->setupButtons();
	}

	else if (currentState == leaderboardState)
	{
		lockBackgroundForDrawing();
		fillBackground(0);
		unlockBackgroundForDrawing();
		currentState->initialiseState();

		// print leaderboard
		readFileAndPrint();
	}
}

void Psyew3Engine::copyAllBackgroundBuffer()
{
	m_pForegroundSurface->copyRectangleFrom(m_pBackgroundSurface, 0, 0, getWindowWidth(), getWindowHeight(), Offset, 0);
	m_pForegroundSurface->copyRectangleFrom(m_pBackgroundSurface, getWindowWidth() - Offset, 0, getWindowWidth(), getWindowHeight(), Offset - getWindowWidth(), 0);
}

void Psyew3Engine::virtMainLoopDoBeforeUpdate()
{
	if (currentState == startUpState)
	{
		for (int i = 0; i < in; i++)
		{
			m_filterScaling.stretch();
		}
		for (int i = 0; i < out; i++)
		{
			m_filterScaling.compress();
		}

		in = 0;
		out = 0;

		lockBackgroundForDrawing();
		virtSetupBackgroundBuffer();
		unlockBackgroundForDrawing();
	}
	Offset = (Offset + 1) % getWindowWidth();
	this->redrawDisplay();
}
void Psyew3Engine::virtKeyDown(int iKeyCode)
{
	if (currentState == endState)
	{
		endState->scanInput(iKeyCode);
	}

	if (currentState == leaderboardState)
	{
		switch (iKeyCode)
		{
		case SDLK_RIGHT:
			m_filterTranslation.changeOffset(10, 0);
			redrawDisplay();
			break;
		case SDLK_LEFT:
			m_filterTranslation.changeOffset(-10, 0);
			redrawDisplay();
			break;
		case SDLK_UP:
			m_filterTranslation.changeOffset(0, 10);
			redrawDisplay();
			break;
		case SDLK_DOWN:
			m_filterTranslation.changeOffset(0, -10);
			redrawDisplay();
			break;
		case SDLK_q:
			lockBackgroundForDrawing();
			virtSetupBackgroundBuffer();
			unlockBackgroundForDrawing();
			currentState = startUpState;
			
		case SDLK_SPACE:
			m_filterTranslation.setOffset(0, 0);
			redrawDisplay();
			break;

		}
	}
}

void Psyew3Engine::virtCreateSurfaces()
{
	BaseEngine::virtCreateSurfaces();
}

void Psyew3Engine::resetAllObjects()
{
	gameState->ballObject->resetObject();
	gameState->racket->resetObject();
	gameState->rock->resetObject();
}

void Psyew3Engine::freeStates()
{
	delete startUpState;
	delete gameState;
	delete leaderboardState;
	delete pauseState;
	delete endState;
}

void Psyew3Engine::readFileAndPrint()
{
	fstream file;
	file.open("file.csv", ios::in);
	int lineCount = 1;

		string line;
		while (getline(file, line) && lineCount < 6) 
		{
			if (lineCount == 1)
			{
				strcpy(firstLine, line.c_str());
				lockForegroundForDrawing();
				drawForegroundString(100, 100, firstLine, 0xFFFFFF, NULL);
				unlockForegroundForDrawing();
			}

			if (lineCount == 2)
			{
				strcpy(secondLine, line.c_str());
				lockForegroundForDrawing();
				drawForegroundString(100, 150, secondLine, 0xFFFFFF, NULL);
				unlockForegroundForDrawing();
			}

			if (lineCount == 3)
			{
				strcpy(thirdLine, line.c_str());
				lockForegroundForDrawing();
				drawForegroundString(100, 200, thirdLine, 0xFFFFFF, NULL);
				unlockForegroundForDrawing();
			}

			if (lineCount == 4)
			{
				strcpy(fourthLine, line.c_str());
				lockForegroundForDrawing();
				drawForegroundString(100, 250, fourthLine, 0xFFFFFF, NULL);
				unlockForegroundForDrawing();
			}

			if (lineCount == 5)
			{
				strcpy(fifthLine, line.c_str());
				lockForegroundForDrawing();
				drawForegroundString(100, 300, fifthLine, 0xFFFFFF, NULL);
				unlockForegroundForDrawing();
			}
			
			lineCount++;
		}
}
