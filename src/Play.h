#pragma once
#include "State.h"
#include "SimpleImage.h"
#include "Ball.h"
#include "Racket.h"
#include "Psyew3Engine.h"
#include "Rock.h"
class Play :
    public State
{
public:
    Play(Psyew3Engine* e) { engine = e; }
    void initialiseState() override;
    void updateState(int) override;

    const SimpleImage gameTheme = ImageManager::get()->getImagebyURL("space_background.PNG", true, true);

    Ball* ballObject;
    Racket* racket;
    Rock* rock;
    Psyew3Engine* engine;
};

