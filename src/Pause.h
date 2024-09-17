#pragma once
#include "State.h"
#include "Psyew3Engine.h"
class Pause :
    public State
{
public:
    Pause(Psyew3Engine* e) { engine = e; }
    void initialiseState() override;
    void setupButtons();
    SimpleImage pauseBackground = ImageManager::get()->getImagebyURL("space_background.png", true, true);
    Psyew3Engine* engine;
};

