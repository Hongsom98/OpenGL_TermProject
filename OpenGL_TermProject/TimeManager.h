#pragma once

#include "Globals.h"

#define GET_TIMEMANAGER TimeManager::Instance()
#define DELTATIME TimeManager::Instance()->GetDeltaTime()

class TimeManager
{
public:
    int mCurFrameLate;
public:
    TimeManager();
    ~TimeManager();

    double GetDeltaTime();
    double CalDeltaTime();
    void SetCurTime();
    void SetPreTime();
    int GetFrameLate();

private:
    int mPreFrameLate;
    double mFrameTime;
    double mDeltaTime;
    std::chrono::system_clock::time_point mCurTime;
    std::chrono::system_clock::time_point mPreTime;

public:
    static TimeManager* Instance()
    {
        static TimeManager* TimeManagerInstance = nullptr;
        if (TimeManagerInstance == nullptr)
            TimeManagerInstance = new TimeManager;

        return TimeManagerInstance;
    }
};
