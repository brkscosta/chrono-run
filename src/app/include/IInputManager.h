#pragma once

#include <SFML/Window/Keyboard.hpp>

namespace app::ui::events {

class IInputManager
{
public:
    virtual ~IInputManager() = default;

    virtual void onKeyReleased(sf::Keyboard::Key key) = 0;
    virtual void onKeyPressed(sf::Keyboard::Key key) = 0;
};

}   // namespace app::ui::events