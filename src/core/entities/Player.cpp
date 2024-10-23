#include "Player.h"

using namespace core::entities;

Player::Player(float x, float y, int life, float speed, PlayerState state)
    : m_xPosition(x)
    , m_yPosition(y)
    , m_life(life)
    , m_speed(speed)
    , m_state(state)
{
}

float Player::getX() const
{
    return m_xPosition;
}

float Player::getY() const
{
    return m_yPosition;
}

int Player::getLife() const
{
    return m_life;
}

float Player::getSpeed() const
{
    return m_speed;
}

void Player::setState(PlayerState state)
{
    m_state = state;
}

void Player::setSpeed(float speed)
{
    m_speed = speed;
}

void Player::setX(float x)
{
    m_xPosition = x;
}

void Player::setY(float y)
{
    m_yPosition = y;
}

void Player::setLife(int life)
{
    m_life = life;
}

PlayerState Player::getState() const
{
    return m_state;
}
