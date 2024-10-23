#include "include/ITimeState.h"

#include <gmock/gmock.h>

namespace core::entities {

class MockTimeState : public ITimeState
{
public:
    MOCK_CONST_METHOD0(getCurrentTime, float());
    MOCK_CONST_METHOD0(getTimeScale, float());
    MOCK_METHOD1(setCurrentTime, void(float));
    MOCK_METHOD1(setTimeScale, void(float scale));
};

}   // namespace core::entities