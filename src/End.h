#pragma once
#include "State.h"
#include "Psyew3Engine.h"
class End :
    public State
{
public:
    End(Psyew3Engine* e) { engine = e; }

    void initialiseState() override;
    void setScore(int);
    void scanInput(int);
    void printName();
    std::vector<char> inputBuf;
    int finalScore;
    Psyew3Engine* engine;
};

