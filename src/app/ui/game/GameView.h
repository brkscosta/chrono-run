#pragma once

#include "include/IGameViewEvent.h"
#include <SFML/Graphics/RenderWindow.hpp>

#include <memory>

namespace app::ui::viewmodels {
class IGameViewModel;
}

namespace app::ui::views {
class GameView : public events::IGameViewEvent
{
public:
    GameView(const std::shared_ptr<app::ui::viewmodels::IGameViewModel>& viewModel);
    ~GameView() override = default;

    void onPause() override;
    void onUpdate() override;

private:
    std::shared_ptr<sf::RenderWindow> m_window;
    std::shared_ptr<sf::Event> m_event;
    std::shared_ptr<app::ui::viewmodels::IGameViewModel> m_viewModel;
};

}   // namespace app::ui::views