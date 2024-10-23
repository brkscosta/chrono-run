#include "GameView.h"

#include "GameViewModel.h"
#include "config.h"
#include "include/IGameViewModel.h"

#include <iostream>

using namespace app::ui::views;

GameView::GameView(const std::shared_ptr<app::ui::viewmodels::IGameViewModel>& viewModel)
    : m_viewModel(viewModel)
{
}

void GameView::onPause()
{
    if (!m_viewModel->isGamePaused())
    {
        m_viewModel->togglePause();
    }
}

void GameView::onUpdate()
{
    m_viewModel->updateTimeController();
}
