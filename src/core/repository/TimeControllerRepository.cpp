#include "TimeControllerRepository.h"

#include "entities/TimeState.h"

#include <memory>
#include <utility>

using namespace core::repository;

TimeControllerRepository::TimeControllerRepository(const std::shared_ptr<core::entities::TimeState>& timeState)
    : m_paused(false)
    , m_timeState(timeState)
    , m_clock(std::make_unique<sf::Clock>())
{
}

void TimeControllerRepository::updateTime()
{
    m_deltaTime = m_clock->restart().asSeconds();

    if (!m_paused)
    {
        float adjustedTime = m_deltaTime * m_timeState->getTimeScale();
        m_timeState->setCurrentTime(m_timeState->getCurrentTime() + adjustedTime);
    }
}

void TimeControllerRepository::togglePause()
{
    m_paused = !m_paused;
}

void TimeControllerRepository::resume()
{
    m_paused = false;
    m_clock->restart();
}

void TimeControllerRepository::setTimeScale(float scale)
{
    m_timeState->setTimeScale(scale);
}

bool TimeControllerRepository::isPaused()
{
    return m_paused;
}

float TimeControllerRepository::getDeltaTime()
{
    return m_deltaTime;
}
