#include "PlayerView.h"

#include "PlayerViewModel.h"
#include "config.h"
#include "utils/Logger.h"

#include <iostream>

using namespace app::ui::views;

namespace {
constexpr int FRAME_COUNT = 9;
constexpr int FRAME_WIDTH = 900 / FRAME_COUNT;
constexpr int FRAME_HEIGHT = 700 / 7;
constexpr float FRAME_DURATION = 0.20f;
}   // namespace

PlayerView::PlayerView(const std::shared_ptr<ui::viewmodels::IPlayerViewModel>& viewModel)
    : m_viewModel(viewModel)
    , m_sprite(std::make_unique<sf::Sprite>())
    , m_texture(std::make_unique<sf::Texture>())
    , m_frameIndex(0)
    , m_maxFrames(0)
    , m_animationTimer(0.f)
{
}

std::shared_ptr<sf::Sprite> PlayerView::getSprite()
{
    return m_sprite;
}

void PlayerView::onUpdate()
{
    updateAnimation();
}

void PlayerView::onAttackWeak()
{
    LOG_SCOPEUSE();
    m_viewModel->setState(core::entities::PlayerState::AttackWeak);
    LOG_INFO("");
}

void PlayerView::onAttackStrong()
{
    LOG_SCOPEUSE();
    m_viewModel->setState(core::entities::PlayerState::AttackStrong);
    LOG_INFO("");
}

void PlayerView::onDefenseAttack()
{
    LOG_SCOPEUSE();
    m_viewModel->setState(core::entities::PlayerState::DefenseAttack);
    LOG_INFO("");
}

void PlayerView::onTakeDamage()
{
    LOG_SCOPEUSE();
    m_viewModel->setState(core::entities::PlayerState::TakingDamage);
    LOG_INFO("");
}

void PlayerView::onDie()
{
    LOG_SCOPEUSE();
    m_viewModel->setState(core::entities::PlayerState::Dying);
    LOG_INFO("");
}

void PlayerView::onStopMove()
{
    LOG_SCOPEUSE();

    m_viewModel->setState(core::entities::PlayerState::Idle);
    m_sprite->setPosition(m_viewModel->getPlayerPosition());
    LOG_INFO("");
}

void PlayerView::onMove(float x, float y)
{
    LOG_SCOPEUSE();

    m_viewModel->setState(core::entities::PlayerState::Walking);
    m_viewModel->setPlayerPosition(x, y);
    m_sprite->setPosition(m_viewModel->getPlayerPosition());
    LOG_INFO("");
}

void PlayerView::updateAnimation()
{
    float deltaTime = m_viewModel->getDeltaTime();
    m_animationTimer += deltaTime;

    if (m_animationTimer >= FRAME_DURATION)
    {
        m_animationTimer -= FRAME_DURATION;
        ++m_frameIndex;

        auto updateFrame = [&](int maxFrames, int row)
        {
            if (m_frameIndex >= maxFrames)
            {
                m_frameIndex = 0;
                m_viewModel->setState(core::entities::PlayerState::Idle);
            }
            m_sprite->setTextureRect(
                  sf::IntRect(m_frameIndex * FRAME_WIDTH, row * FRAME_HEIGHT, FRAME_WIDTH, FRAME_HEIGHT));
            m_maxFrames = maxFrames;
        };

        switch (m_viewModel->getPlayerState())
        {
            case core::entities::PlayerState::Idle:
                updateFrame(6, 0);
                break;
            case core::entities::PlayerState::Walking:
                updateFrame(8, 1);
                break;
            case core::entities::PlayerState::AttackWeak:
                updateFrame(6, 2);
                break;
            case core::entities::PlayerState::AttackStrong:
                updateFrame(6, 3);
                break;
            case core::entities::PlayerState::DefenseAttack:
                updateFrame(9, 4);
                break;
            case core::entities::PlayerState::TakingDamage:
                updateFrame(4, 5);
                break;
            case core::entities::PlayerState::Dying:
                updateFrame(4, 6);
                break;
        }
    }
}

bool PlayerView::loadTexture()
{
    LOG_SCOPEUSE();

#ifdef NDEBUG
    std::filesystem::path texturePath = SPRITE_ASSETS_PATH PLAYER_SPRITE;
#else
    std::filesystem::path texturePath = "assets/sprites/" PLAYER_SPRITE;
#endif

    if (!std::filesystem::exists(texturePath))
    {
        LOG_ERROR("Player texture not found");
        return false;
    }

    if (!m_texture->loadFromFile(texturePath.string()))
    {
        LOG_ERROR("Error on loading player texture");
        return false;
    }
    m_sprite->setTexture(*m_texture);
    m_sprite->setTextureRect(sf::IntRect(0, 0, FRAME_WIDTH, FRAME_HEIGHT));
    m_sprite->setPosition(m_viewModel->getPlayerPosition());
    m_sprite->setScale(2.5f, 2.5f);

    return true;
}