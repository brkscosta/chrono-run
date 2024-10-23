#pragma once
#include "include/IGameViewModel.h"

#include <memory>

namespace core::repository {
class ITimeControllerRepository;
}

namespace app::ui::viewmodels {
class GameViewModel : public IGameViewModel
{
public:
    GameViewModel(const std::shared_ptr<core::repository::ITimeControllerRepository>& timeControllerRepository);
    ~GameViewModel() override = default;

    void updateTimeController() override;
    bool isGamePaused() override;
    void togglePause() override;

private:
    std::shared_ptr<core::repository::ITimeControllerRepository> m_timeControllerRepository;
};

}   // namespace app::ui::viewmodels