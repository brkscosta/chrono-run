#include "game/GameView.h"

#include "mocks/internalsources/MockGameViewModel.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace testing;
using namespace app::ui;

class GameViewTest : public Test
{
protected:
    std::shared_ptr<NiceMock<viewmodels::MockGameViewModel>> mockViewModel;
    std::unique_ptr<views::GameView> gameView;

    void SetUp() override
    {
        mockViewModel = std::make_shared<NiceMock<viewmodels::MockGameViewModel>>();
        gameView = std::make_unique<views::GameView>(mockViewModel);
    }
};

TEST_F(GameViewTest, OnPause_WhenGameIsNotPaused_ShouldTogglePause)
{
    EXPECT_CALL(*mockViewModel, isGamePaused()).WillOnce(Return(false));
    EXPECT_CALL(*mockViewModel, togglePause()).Times(1);

    gameView->onPause();
}

TEST_F(GameViewTest, OnPause_WhenGameIsPaused_ShouldNotTogglePause)
{
    EXPECT_CALL(*mockViewModel, isGamePaused()).WillOnce(Return(true));
    EXPECT_CALL(*mockViewModel, togglePause()).Times(0);

    gameView->onPause();
}

TEST_F(GameViewTest, OnUpdate_ShouldUpdateTimeController)
{
    EXPECT_CALL(*mockViewModel, updateTimeController()).Times(1);

    gameView->onUpdate();
}