#include "PlayerEventImpl.h"

#include "include/IPlayerEvents.h"
#include "utils/Logger.h"

using namespace app::ui::views;

namespace {
constexpr float AXIS_X_POSITIVE = 1.f;
constexpr float AXIS_Y_POSITIVE = 1.f;
constexpr float AXIS_X_NEGATIVE = -1.f;
constexpr float AXIS_Y_NEGATIVE = -1.f;

const std::vector<sf::Keyboard::Key> movementKeys = {
    sf::Keyboard::W,
    sf::Keyboard::S,
    sf::Keyboard::A,
    sf::Keyboard::D,
};

const std::map<sf::Keyboard::Key, std::pair<float, float>> movementMap = {
    { sf::Keyboard::W, { 0.f, AXIS_Y_NEGATIVE } },
    { sf::Keyboard::S, { 0.f, AXIS_Y_POSITIVE } },
    { sf::Keyboard::A, { AXIS_X_NEGATIVE, 0.f } },
    { sf::Keyboard::D, { AXIS_X_POSITIVE, 0.f } }
};
}   // namespace

PlayerEventImpl::PlayerEventImpl(const std::shared_ptr<events::IPlayerEvents>& playerEvents)
    : m_playerEvents(playerEvents)
{
}

void PlayerEventImpl::onKeyPressed(sf::Keyboard::Key key)
{
    auto it = movementMap.find(key);
    if (it != movementMap.end())
    {
        m_playerEvents->onMove(it->second.first, it->second.second);
    }
    else if (key == sf::Keyboard::Space)
    {
        m_playerEvents->onAttackWeak();
    }
}

void PlayerEventImpl::onKeyReleased(sf::Keyboard::Key key)
{
    if (std::find(movementKeys.begin(), movementKeys.end(), key) != movementKeys.end())
    {
        m_playerEvents->onStopMove();
    }
}
