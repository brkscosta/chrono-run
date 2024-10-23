#include "TimeState.h"

using namespace core::entities;

TimeState::TimeState(const float currentTime, const float timeScale)
    : currentTime(currentTime)
    , timeScale(timeScale)
{
}

float TimeState::getCurrentTime() const
{
    return currentTime;
}

float TimeState::getTimeScale() const
{
    return timeScale;
}

void TimeState::setCurrentTime(float time)
{
    currentTime = time;
}

void TimeState::setTimeScale(float scale)
{
    timeScale = scale;
}
