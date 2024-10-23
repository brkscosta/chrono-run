#include "UiEvent.h"

using namespace app::ui::events;

UiEvent::UiEvent(const std::shared_ptr<app::ui::events::IGameViewEvent>& gameViewEvent)
    : m_gameViewEvent(gameViewEvent)
{
}

void UiEvent::onKeyPressed(sf::Keyboard::Key key)
{
    if (key == sf::Keyboard::P || key == sf::Keyboard::Escape)
    {
        m_gameViewEvent->onPause();
    }
}
