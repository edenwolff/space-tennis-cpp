#pragma once
#include "GameObject.h"
class Racket :
    public GameObject
{
public:
    Racket(int x, int y, int width, int height, Psyew3Engine* engine) : GameObject(x, y, width, height, engine)
    {
        objectImage = ImageManager::get()->getImagebyURL("racket1.png", true, true);
    };

    void virtDraw() override;
    void virtDoUpdate(int time) override;
    void detectCollision();
    void resetObject() override;

private:
    bool right;
    SimpleImage oImage;
};

