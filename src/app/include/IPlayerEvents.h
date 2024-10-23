#pragma once

#include "IGraphicalObject.h"

namespace app::ui::events {
class IPlayerEvents : public IGraphicalObject
{
public:
    ~IPlayerEvents() override = default;

    virtual void onMove(float x, float y) = 0;
    virtual void onAttackWeak() = 0;
    virtual void onAttackStrong() = 0;
    virtual void onDefenseAttack() = 0;
    virtual void onTakeDamage() = 0;
    virtual void onDie() = 0;
    virtual void onStopMove() = 0;
};
}   // namespace app::ui::events