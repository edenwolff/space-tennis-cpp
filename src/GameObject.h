#pragma once
#include "DisplayableObject.h"
#include "SimpleImage.h"
#include "Psyew3Engine.h"
#include "Psyew3TileManager.h"
#include "ObjectMapper.h"
#include <vector>
class GameObject :
    public DisplayableObject
{
protected:
    int speedX, speedY;
    ObjectMapper oMapper;

public:
     /* 2nd constructor without tile manager */
    GameObject(int x, int y, int width, int height, Psyew3Engine* gameEngine) : DisplayableObject(x, y, gameEngine, width, height, true)
        , oMapper()
    {
        speedX = 4;
        speedY = 4;
    };

    // X & Y getters and setters
    int getX() { return m_iCurrentScreenX; }
    int getY() { return m_iCurrentScreenY; }

    void setX(int x) { m_iCurrentScreenX = x; }
    void setY(int y) { m_iCurrentScreenY = y; }

    int getWidth() { return m_iDrawWidth; }
    int getHeight() { return m_iDrawHeight; }

    // Speed getters & setters
    int getSpeedX() { return speedX; }
    int getSpeedY() { return speedY; }

    void setSpeedX(int x) { this->speedX = x; }
    void setSpeedY(int y) { this->speedY = y; }

    std::vector<std::tuple<int,int>> getImageOutline(SimpleImage);

    virtual bool checkCollision(GameObject);

    SimpleImage objectImage;

    //std::vector<std::tuple<int, int>> imageOutline;

    virtual void resetObject();
};

