#pragma once
#include "GameObject.h"
class Ball :
    public GameObject
{
public:
    Ball(int x, int y, int width, int height, Psyew3Engine* engine)
        : GameObject(x, y, width, height, engine) 
        , playerScore(0)
    {
        objectImage = ImageManager::get()->getImagebyURL("tennis_ball.png", true, true);
        selectedBall = ImageManager::get()->getImagebyURL("tennis_ball.png", true, true);
        oBall = ImageManager::get()->getImagebyURL("hit_ball.png", true, true);
    };

    void virtDraw() override;
    void virtDoUpdate(int time) override;
    bool isAlive();
    void detectCollision();
    void resetObject() override;

    SimpleImage oBall;
    SimpleImage selectedBall;

    int playerScore;
};

