#include "RenderEngine.h"

#include "config.h"
#include "include/IGameViewEvent.h"
#include "include/IGraphicalObject.h"
#include "include/IInputManager.h"
#include "include/IPlayerEvents.h"
#include "utils/Logger.h"

#include <memory>
#include <vector>

using namespace app::ui::engine;

RenderEngine::RenderEngine(const std::shared_ptr<sf::RenderWindow>& window,
                           const std::shared_ptr<sf::Event>& event,
                           const int frameRateLimit,
                           const std::vector<std::shared_ptr<app::ui::events::IInputManager>>& inputManagers,
                           const std::vector<std::shared_ptr<ui::events::IGameViewEvent>>& gameViewEvents,
                           const std::shared_ptr<ui::events::IPlayerEvents>& playerObject)
    : m_window(window)
    , m_event(event)
    , m_inputManagers(inputManagers)
    , m_gameViewEvents(gameViewEvents)
    , m_playerObject(playerObject)
    , m_frameRateLimit(frameRateLimit)
{
}

bool RenderEngine::init()
{
    LOG_SCOPEUSE();
    if (m_frameRateLimit < 0)
    {
        m_window->setFramerateLimit(INITIAL_FRAMERATE);
    }
    else
    {
        m_window->setFramerateLimit(m_frameRateLimit);
    }

    if (!m_playerObject->loadTexture())
    {
        LOG_ERROR("Failed to load texture");
        return false;
    }

    return true;
}

void RenderEngine::run()
{
    while (m_window->isOpen())
    {
        processEvents();
        update();
        render();
    }
}

void RenderEngine::changeFrameRateLimit(const int frameRateLimit)
{
    m_frameRateLimit = frameRateLimit;
    m_window->setFramerateLimit(m_frameRateLimit);
}

void RenderEngine::processEvents()
{
    while (m_window->pollEvent(*m_event))
    {
        if (m_event->type == sf::Event::Closed)
        {
            m_window->close();
        }

        if (m_event->type == sf::Event::KeyPressed)
        {
            for (const auto& instance : m_inputManagers)
            {
                instance->onKeyPressed(m_event->key.code);
            }
        }
        else if (m_event->type == sf::Event::KeyReleased)
        {
            for (const auto& instance : m_inputManagers)
            {
                instance->onKeyReleased(m_event->key.code);
            }
        }
    }
}

void RenderEngine::update()
{
    for (const auto& instance : m_gameViewEvents)
    {
        instance->onUpdate();
    }

    m_playerObject->onUpdate();
}

void RenderEngine::render()
{
    m_window->clear();
    m_window->draw(*m_playerObject->getSprite());
    m_window->display();
}