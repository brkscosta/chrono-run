#pragma once
#include "ITimeControllerRepository.h"
#include <SFML/System/Clock.hpp>

#include <memory>

namespace core::entities {
class TimeState;
}

namespace core::repository {

class TimeControllerRepository : public ITimeControllerRepository
{
public:
    TimeControllerRepository(const std::shared_ptr<core::entities::TimeState>& timeState);
    ~TimeControllerRepository() override = default;

    void updateTime() override;

    void togglePause() override;
    void resume() override;
    void setTimeScale(float scale) override;
    bool isPaused() override;
    float getDeltaTime() override;

private:
    std::shared_ptr<core::entities::TimeState> m_timeState;
    std::unique_ptr<sf::Clock> m_clock;

    bool m_paused;
    float m_deltaTime;
};

}   // namespace core::repository
