#pragma once
#include "GameObject.h"
class Rock :
    public GameObject
{
public:
    Rock(int x, int y, int width, int height, Psyew3Engine* engine) : GameObject(x, y, width, height, engine)
        , tickOffset(0)
        , move(false)
    {
        objectImage = ImageManager::get()->getImagebyURL("rock.png", true, true);
        speedX = 5;
        speedY = 5;

    };
    void virtDraw() override;
    void virtDoUpdate(int) override;
    void resetObject() override;
    void calculatePath();

    int tickOffset;
    bool move;
};

