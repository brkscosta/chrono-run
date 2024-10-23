#pragma once
#include "Logger.h"
#include "include/IPlayer.h"

#include <ostream>

std::ostream& operator<<(std::ostream& os, const core::entities::IPlayer& player)
{
    os << "Player(";
    os << "x: " << player.getX() << ", ";
    os << "y: " << player.getY() << ", ";
    os << "life: " << player.getLife() << ", ";
    os << "speed: " << player.getSpeed() << ", ";
    os << "state: " << player.getState();
    os << ")";
    return os;
}

std::ostream& operator<<(std::ostream& os, const core::entities::PlayerState& state)
{
    switch (state)
    {
        case core::entities::Idle:
            os << "Idle";
            break;
        case core::entities::Walking:
            os << "Walking";
            break;
        case core::entities::AttackWeak:
            os << "AttackWeak";
            break;
        case core::entities::AttackStrong:
            os << "AttackStrong";
            break;
        case core::entities::DefenseAttack:
            os << "DefenseAttack";
            break;
        case core::entities::TakingDamage:
            os << "TakingDamage";
            break;
        case core::entities::Dying:
            os << "Dying";
            break;
        default:
            os << "Unknown";
            break;
    }
    return os;
}
