#pragma once

namespace app::ui::events {

class IGameViewEvent
{
public:
    virtual ~IGameViewEvent() = default;

    virtual void onPause() = 0;
    virtual void onUpdate() = 0;
};

}   // namespace app::ui::events