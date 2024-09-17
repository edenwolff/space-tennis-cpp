#pragma once
#include "TileManager.h"
#include "ObjectMapper.h"
class Psyew3TileManager :
    public TileManager
{
public:
    Psyew3TileManager()
        : TileManager(100, 100, 2, 2) , oMapper()
    {
    }

    ObjectMapper oMapper;

    SimpleImage racket = ImageManager::get()->getImagebyURL("racket1.png", true, true);
    const SimpleImage selectedRacket = ImageManager::get()->getImagebyURL("racket_selected.png", true, true);

    SimpleImage racket2 = ImageManager::get()->getImagebyURL("racket2.png", true, true);
    const SimpleImage selectedRacket2 = ImageManager::get()->getImagebyURL("selected_racket2.png", true, true);

    SimpleImage ballSkin = ImageManager::get()->getImagebyURL("skin_ball.png", true, true);
    const SimpleImage selectedball1 = ImageManager::get()->getImagebyURL("selected_ball1.png", true, true);

    SimpleImage orangeBallSkin = ImageManager::get()->getImagebyURL("ball2_skin.png", true, true);
    const SimpleImage selectedball2 = ImageManager::get()->getImagebyURL("selected_ball2.png", true, true);

    virtual void virtDrawTileAt(
        BaseEngine* pEngine,
        DrawingSurface* pSurface,
        int iMapX, int iMapY,
        int iStartPositionScreenX, int iStartPositionScreenY) const override;



};

