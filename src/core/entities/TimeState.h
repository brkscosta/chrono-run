#pragma once
#include "ITimeState.h"
namespace core::entities {

class TimeState : public ITimeState
{
public:
    TimeState(float currentTime = 0.0f, float timeScale = 1.0f);

    float getCurrentTime() const override;
    float getTimeScale() const override;

    void setCurrentTime(float time) override;
    void setTimeScale(float scale) override;

private:
    float currentTime;
    float timeScale;
};

}   // namespace core::entities
