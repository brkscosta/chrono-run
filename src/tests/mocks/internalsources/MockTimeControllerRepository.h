#pragma once

#include "include/ITimeControllerRepository.h"

#include <gmock/gmock.h>

namespace core::repository {
class MockTimeControllerRepository : public ITimeControllerRepository
{
public:
    ~MockTimeControllerRepository() override = default;
    MOCK_METHOD(void, updateTime, (), ());
    MOCK_METHOD(void, togglePause, (), ());
    MOCK_METHOD(void, resume, (), ());
    MOCK_METHOD(void, setTimeScale, (float), ());
    MOCK_METHOD(bool, isPaused, (), ());
    MOCK_METHOD(float, getDeltaTime, (), ());
};
}   // namespace core::repository