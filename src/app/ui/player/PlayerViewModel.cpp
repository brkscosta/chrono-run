#include "PlayerViewModel.h"

#include "Printers.h"
#include "include/IPlayer.h"
#include "include/ITimeControllerRepository.h"
#include "utils/Logger.h"

using namespace app::ui::viewmodels;

PlayerViewModel::PlayerViewModel(const std::shared_ptr<core::entities::IPlayer>& player,
                                 const std::shared_ptr<core::repository::ITimeControllerRepository>& timeController)
    : m_player(player)
    , m_timeControllerRepository(timeController)
{
    LOG_SCOPEUSE();
    LOG_INFO("Inital Player state: " << *m_player);
}

core::entities::PlayerState PlayerViewModel::getPlayerState() const
{
    return m_player->getState();
}

void PlayerViewModel::setState(core::entities::PlayerState state)
{
    LOG_SCOPEUSE();

    m_player->setState(state);
    LOG_INFO("Player state: " << *m_player);
}

float PlayerViewModel::getX() const
{
    return m_player->getX();
}

float PlayerViewModel::getY() const
{
    return m_player->getY();
}

int PlayerViewModel::getLife() const
{
    return m_player->getLife();
}

void PlayerViewModel::setPlayerPosition(float x, float y)
{
    float deltaTime = m_timeControllerRepository->getDeltaTime();

    float newX = m_player->getX() + (x * m_player->getSpeed() * deltaTime);
    float newY = m_player->getY() + (y * m_player->getSpeed() * deltaTime);

    m_player->setX(newX);
    m_player->setY(newY);
}

sf::Vector2f PlayerViewModel::getPlayerPosition()
{
    return sf::Vector2f(m_player->getX(), m_player->getY());
}

float PlayerViewModel::getDeltaTime()
{
    return m_timeControllerRepository->getDeltaTime();
}

void PlayerViewModel::setLife(int life)
{
    m_player->setLife(life);
}