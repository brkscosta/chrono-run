#pragma once

#include "include/IPlayerEvents.h"
#include "include/IRenderEngine.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>

#include <memory>
#include <vector>

namespace app::ui::events {
class IInputManager;
class IGameViewEvent;
}   // namespace app::ui::events

namespace app::ui::engine {

class RenderEngine : public IRenderEngine
{
public:
    RenderEngine(const std::shared_ptr<sf::RenderWindow>& window,
                 const std::shared_ptr<sf::Event>& event,
                 int frameRateLimit,
                 const std::vector<std::shared_ptr<events::IInputManager>>& inputManagers,
                 const std::vector<std::shared_ptr<events::IGameViewEvent>>& gameViewEvents,
                 const std::shared_ptr<events::IPlayerEvents>& playerObject);
    ~RenderEngine() override = default;

    bool init() override;
    void run() override;
    void changeFrameRateLimit(int frameRateLimit) override;

private:
    void processEvents();
    void update();
    void render();

    std::shared_ptr<sf::RenderWindow> m_window;
    std::shared_ptr<sf::Event> m_event;
    std::vector<std::shared_ptr<app::ui::events::IInputManager>> m_inputManagers;
    std::vector<std::shared_ptr<ui::events::IGameViewEvent>> m_gameViewEvents;
    std::shared_ptr<app::ui::events::IPlayerEvents> m_playerObject;

    int m_frameRateLimit;
};

}   // namespace app::ui::engine