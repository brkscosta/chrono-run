#pragma once
#include <SFML/Graphics.hpp>

#include <memory>
namespace app::ui {

class IGraphicalObject
{
public:
    virtual ~IGraphicalObject() = default;

    virtual bool loadTexture() = 0;
    virtual void onUpdate() = 0;
    virtual std::shared_ptr<sf::Sprite> getSprite() = 0;
};

}   // namespace app::ui