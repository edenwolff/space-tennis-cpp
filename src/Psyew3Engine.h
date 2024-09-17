#pragma once
#include "BaseEngine.h"
#include "Psyew3TileManager.h"
#include "State.h"
#include "ScrollingAndZooming.h"

class Psyew3Engine :
    public BaseEngine
{
public:
    Psyew3Engine() :
        m_filterScaling(0, 0, this)
        , m_filterTranslation(0, 0, &m_filterScaling)
    {
    };

    void virtSetupBackgroundBuffer() override;
    void virtMouseWheel(int x, int y, int which, int timestamp);
    void virtMouseDown(int,int,int) override;
    int virtInitialiseObjects() override;
    void respawnRock();
    void finishGame();
    void updateGame(int);
    void addObjectsToArray();
    void virtDrawStringsUnderneath() override;
    void copyAllBackgroundBuffer();
    virtual void virtMainLoopDoBeforeUpdate() override;
    void virtKeyDown(int) override;
    void resetAllObjects();
    void freeStates();
    void readFileAndPrint();
    int virtInitialise() override;
    virtual void virtCreateSurfaces() override;
    Psyew3TileManager* tileManager;
    int playerScore;
    State* currentState;
    FILE file;

    ~Psyew3Engine() 
    {
        freeStates();
        delete tileManager;
    }

private:
    int Offset;


protected:
    FilterScaling m_filterScaling;
    FilterTranslation m_filterTranslation;
};

