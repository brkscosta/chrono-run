#include "App.h"

#include "config.h"
#include "entities/Player.h"
#include "entities/TimeState.h"
#include "events/UiEvent.h"
#include "game/GameView.h"
#include "game/GameViewModel.h"
#include "include/IGameViewEvent.h"
#include "include/IInputManager.h"
#include "include/IPlayerEvents.h"
#include "player/PlayerEventImpl.h"
#include "player/PlayerView.h"
#include "player/PlayerViewModel.h"
#include "repository/TimeControllerRepository.h"
#include "ui/engine/RenderEngine.h"
#include "utils/Logger.h"

#include <iostream>
#include <string>

using namespace app;

App::App()
{
    init();
}

void App::start()
{
    LOG_SCOPEUSE();

    if (!m_renderEngine->init())
    {
        LOG_ERROR("Failed to initialize render engine");
        return;
    }

    LOG_INFO("App started, version: " + std::string(APP_VERSION) + ", build: " + std::string(GIT_COMMIT_HASH));
    m_renderEngine->run();
}

void App::init()
{
    auto window = std::make_shared<sf::RenderWindow>(sf::VideoMode(INITIAL_WINDOW_WIDTH, INITIAL_WINDOW_HEIGHT),
                                                     APP_NAME);
    auto event = std::make_shared<sf::Event>();
    auto timeState = std::make_shared<core::entities::TimeState>();

    auto timeController = std::make_shared<core::repository::TimeControllerRepository>(timeState);
    auto player = std::make_shared<core::entities::Player>();

    auto playerViewModel = std::make_shared<ui::viewmodels::PlayerViewModel>(player, timeController);
    auto playerView = std::make_shared<ui::views::PlayerView>(playerViewModel);

    auto gameViewModel = std::make_shared<ui::viewmodels::GameViewModel>(timeController);
    auto gameView = std::make_shared<ui::views::GameView>(gameViewModel);

    auto playerEventImpl = std::make_shared<ui::views::PlayerEventImpl>(playerView);
    auto uiEvent = std::make_shared<ui::events::UiEvent>(gameView);

    auto inputManagers = std::vector<std::shared_ptr<ui::events::IInputManager>> { playerEventImpl, uiEvent };
    auto gameViewEvents = std::vector<std::shared_ptr<ui::events::IGameViewEvent>> { gameView };

    m_renderEngine = std::make_shared<app::ui::engine::RenderEngine>(
          window, event, 60, inputManagers, gameViewEvents, playerView);
}
