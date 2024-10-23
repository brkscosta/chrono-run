#pragma once
#include "include/IInputManager.h"
#include <SFML/Window/Keyboard.hpp>

#include <functional>
#include <map>
#include <memory>
#include <vector>

namespace app::ui::events {
class IPlayerEvents;
}   // namespace app::ui::events

namespace app::ui::views {

class PlayerEventImpl : public events::IInputManager
{
public:
    PlayerEventImpl(const std::shared_ptr<events::IPlayerEvents>& playerEvents);
    ~PlayerEventImpl() override = default;

    void onKeyReleased(sf::Keyboard::Key key) override;
    void onKeyPressed(sf::Keyboard::Key key) override;

private:
    void move(float x, float y);

    std::shared_ptr<events::IPlayerEvents> m_playerEvents;
};

}   // namespace app::ui::views