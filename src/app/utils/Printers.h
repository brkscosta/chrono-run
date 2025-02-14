#pragma once
#include "include/IPlayer.h"

#include <ostream>

std::ostream& operator<<(std::ostream& os, core::entities::PlayerState state);

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

std::ostream& operator<<(std::ostream& os, const core::entities::PlayerState state)
{
    switch (state)
    {
        case core::entities::PlayerState::Idle:
            os << "Idle";
            break;
        case core::entities::PlayerState::Walking:
            os << "Walking";
            break;
        case core::entities::PlayerState::AttackWeak:
            os << "AttackWeak";
            break;
        case core::entities::PlayerState::AttackStrong:
            os << "AttackStrong";
            break;
        case core::entities::PlayerState::DefenseAttack:
            os << "DefenseAttack";
            break;
        case core::entities::PlayerState::TakingDamage:
            os << "TakingDamage";
            break;
        case core::entities::PlayerState::Dying:
            os << "Dying";
            break;
        default:
            os << "Unknown";
            break;
    }
    return os;
}
