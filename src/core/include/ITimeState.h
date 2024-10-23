#pragma once

namespace core::entities {
class ITimeState
{
public:
    virtual ~ITimeState() = default;
    virtual float getCurrentTime() const = 0;
    virtual float getTimeScale() const = 0;
    virtual void setCurrentTime(float time) = 0;
    virtual void setTimeScale(float scale) = 0;
};
}   // namespace core::entities