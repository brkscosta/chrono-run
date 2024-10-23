#include "GameViewModel.h"
#include "repository/TimeControllerRepository.h"

using namespace app::ui::viewmodels;

GameViewModel::GameViewModel(
      const std::shared_ptr<core::repository::ITimeControllerRepository>& timeControllerRepository)
    : m_timeControllerRepository(timeControllerRepository)
{
}

void GameViewModel::updateTimeController()
{
    m_timeControllerRepository->updateTime();
}

bool GameViewModel::isGamePaused()
{
    return m_timeControllerRepository->isPaused();
}

void GameViewModel::togglePause()
{
    m_timeControllerRepository->togglePause();
}