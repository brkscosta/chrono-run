#pragma once
#include "IPlayer.h"
#include <SFML/System/Vector2.hpp>
namespace core::entities {

class Player : public IPlayer
{
public:
    Player(float x = 100.f,
           float y = 200.f,
           int life = 100,
           float speed = 200.0f,
           PlayerState state = PlayerState::Idle);
    ~Player() override = default;

    float getX() const override;
    float getY() const override;
    int getLife() const override;
    float getSpeed() const override;
    PlayerState getState() const override;

    void setX(float x) override;
    void setY(float y) override;
    void setLife(int life) override;
    void setSpeed(float speed) override;
    void setState(PlayerState state) override;

private:
    float m_xPosition;
    float m_yPosition;
    float m_speed;
    int m_life;
    PlayerState m_state;
};
}   // namespace core::entities
