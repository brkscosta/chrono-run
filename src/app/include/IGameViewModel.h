#pragma once

namespace app::ui::viewmodels {
class IGameViewModel
{
public:
    virtual ~IGameViewModel() = default;

    virtual void updateTimeController() = 0;
    virtual bool isGamePaused() = 0;
    virtual void togglePause() = 0;
};
}   // namespace app::ui::viewmodels