#pragma once
#include "include/IPlayerEvents.h"

#include <gmock/gmock.h>

namespace app::ui::events {

class MockPlayerEvents : public IPlayerEvents
{
public:
    ~MockPlayerEvents() override = default;
    MOCK_METHOD(void, onMove, (float x, float y), (override));
    MOCK_METHOD(void, onAttackWeak, (), (override));
    MOCK_METHOD(void, onAttackStrong, (), (override));
    MOCK_METHOD(void, onDefenseAttack, (), (override));
    MOCK_METHOD(void, onTakeDamage, (), (override));
    MOCK_METHOD(void, onDie, (), (override));
    MOCK_METHOD(void, onStopMove, (), (override));
    MOCK_METHOD(bool, loadTexture, (), (override));
    MOCK_METHOD(void, onUpdate, (), (override));
    MOCK_METHOD(std::shared_ptr<sf::Sprite>, getSprite, (), (override));
};

}   // namespace app::ui::events