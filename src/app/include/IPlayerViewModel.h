#pragma once
#include "include/IPlayer.h"
#include <SFML/System/Vector2.hpp>

namespace app::ui::viewmodels {
class IPlayerViewModel
{
public:
    virtual ~IPlayerViewModel() = default;

    virtual void setPlayerPosition(float x, float y) = 0;
    virtual void setLife(int life) = 0;
    virtual sf::Vector2f getPlayerPosition() = 0;
    virtual core::entities::PlayerState getPlayerState() const = 0;
    virtual void setState(core::entities::PlayerState state) = 0;
    virtual float getDeltaTime() = 0;
};

}   // namespace app::ui::viewmodels
