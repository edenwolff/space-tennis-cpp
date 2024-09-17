#pragma once
#include "State.h"
#include "Psyew3Engine.h"

using namespace std;

    class Leaderboard :
        public State
    {
    public:
        Leaderboard(Psyew3Engine* engine)
        {
            this->engine = engine;
        }
        void initialiseState() override;
        const SimpleImage background = ImageManager::get()->getImagebyURL("space_background.png", true, true);
        Psyew3Engine* engine;
    };