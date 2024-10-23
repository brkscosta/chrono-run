#pragma once
#include "include/IPlayerEvents.h"
#include "include/IPlayerViewModel.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>

#include <filesystem>
#include <iostream>
#include <memory>

#include <cstdint>

namespace core::entities {
class Player;

}   // namespace core::entities

namespace app::ui::views {

class PlayerView : public events::IPlayerEvents
{
public:
    PlayerView(const std::shared_ptr<ui::viewmodels::IPlayerViewModel>& viewModel);
    ~PlayerView() override = default;

    std::shared_ptr<sf::Sprite> getSprite() override;
    bool loadTexture() override;
    void onUpdate() override;

    void onMove(float x, float y) override;
    void onAttackWeak() override;
    void onAttackStrong() override;
    void onDefenseAttack() override;
    void onTakeDamage() override;
    void onDie() override;
    void onStopMove() override;

private:
    void updateAnimation();

    std::shared_ptr<ui::viewmodels::IPlayerViewModel> m_viewModel;
    std::shared_ptr<sf::Sprite> m_sprite;
    std::unique_ptr<sf::Texture> m_texture;
    float m_animationTimer;
    int m_maxFrames;
    int m_frameIndex;
};
}   // namespace app::ui::views