#pragma once

namespace core::entities {
enum PlayerState
{
    Idle,
    Walking,
    AttackWeak,
    AttackStrong,
    DefenseAttack,
    TakingDamage,
    Dying
};

class IPlayer
{
public:
    virtual ~IPlayer() = default;
    virtual float getX() const = 0;
    virtual float getY() const = 0;
    virtual int getLife() const = 0;
    virtual float getSpeed() const = 0;
    virtual void setX(float x) = 0;
    virtual void setY(float y) = 0;
    virtual void setLife(int life) = 0;
    virtual void setSpeed(float speed) = 0;
    virtual void setState(PlayerState state) = 0;
    virtual PlayerState getState() const = 0;
};

}   // namespace core::entities