#pragma once

namespace core::repository {
class ITimeControllerRepository
{
public:
    virtual ~ITimeControllerRepository() = default;

    virtual void updateTime() = 0;

    virtual void togglePause() = 0;
    virtual void resume() = 0;
    virtual void setTimeScale(float scale) = 0;
    virtual bool isPaused() = 0;
    virtual float getDeltaTime() = 0;
};
}   // namespace core::repository