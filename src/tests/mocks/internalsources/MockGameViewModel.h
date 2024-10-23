#pragma once
#include "include/IGameViewModel.h"

#include <gmock/gmock.h>

namespace app::ui::viewmodels {
class MockGameViewModel : public IGameViewModel
{
public:
    ~MockGameViewModel() override = default;
    MOCK_METHOD(void, updateTimeController, (), ());
    MOCK_METHOD(bool, isGamePaused, (), ());
    MOCK_METHOD(void, togglePause, (), ());
};
}   // namespace app::ui::viewmodels