#pragma once
#include "include/IPlayerViewModel.h"

#include <memory>

namespace core::entities {
class IPlayer;
}   // namespace core::entities

namespace core::repository {
class ITimeControllerRepository;
}

namespace app::ui::viewmodels {
class PlayerViewModel : public IPlayerViewModel
{
public:
    PlayerViewModel(const std::shared_ptr<core::entities::IPlayer>& player,
                    const std::shared_ptr<core::repository::ITimeControllerRepository>& timeController);
    ~PlayerViewModel() override = default;

    float getX() const;
    float getY() const;
    int getLife() const;

    void setPlayerPosition(float x, float y) override;
    void setLife(int life) override;
    sf::Vector2f getPlayerPosition() override;
    core::entities::PlayerState getPlayerState() const override;
    void setState(core::entities::PlayerState state) override;
    float getDeltaTime() override;

private:
    std::shared_ptr<core::entities::IPlayer> m_player;
    std::shared_ptr<core::repository::ITimeControllerRepository> m_timeControllerRepository;
};

}   // namespace app::ui::viewmodels