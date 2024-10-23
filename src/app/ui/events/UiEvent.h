#pragma once

#include "include/IGameViewEvent.h"
#include "include/IInputManager.h"

#include <memory>

namespace app::ui::events {
class UiEvent : public events::IInputManager
{
public:
    UiEvent(const std::shared_ptr<app::ui::events::IGameViewEvent>& gameViewEvent);
    ~UiEvent() override = default;

    void onKeyPressed(sf::Keyboard::Key key) override;
    void onKeyReleased(sf::Keyboard::Key key) override {};

private:
    std::shared_ptr<app::ui::events::IGameViewEvent> m_gameViewEvent;
};
}   // namespace app::ui::events