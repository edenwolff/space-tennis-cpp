#pragma once
#include "State.h"
#include "SimpleImage.h"
#include "Psyew3Engine.h"
class Menu :
    public State
{
public:
    Menu(Psyew3Engine* e) { engine = e; }
    void initialiseState() override;
    Psyew3Engine* engine;
    SimpleImage selectedBall;
    SimpleImage selecedRacket;
};