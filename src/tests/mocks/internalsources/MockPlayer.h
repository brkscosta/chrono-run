#pragma once
#include "include/IPlayer.h"

#include <gmock/gmock.h>

namespace core::entities {
class MockPlayer : public IPlayer
{
public:
    ~MockPlayer() override = default;

    MOCK_METHOD(PlayerState, getState, (), (const, override));
    MOCK_METHOD(void, setState, (PlayerState state), (override));
    MOCK_METHOD(float, getX, (), (const, override));
    MOCK_METHOD(float, getY, (), (const, override));
    MOCK_METHOD(float, getSpeed, (), (const, override));
    MOCK_METHOD(int, getLife, (), (const, override));
    MOCK_METHOD(void, setX, (float x), (override));
    MOCK_METHOD(void, setY, (float y), (override));
    MOCK_METHOD(void, setLife, (int life), (override));
};

}   // namespace core::entities