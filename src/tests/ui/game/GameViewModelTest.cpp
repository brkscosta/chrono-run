#include "ui/game/GameViewModel.h"

#include "entities/TimeState.h"
#include "mocks/internalsources/MockTimeControllerRepository.h"
#include "mocks/internalsources/MockTimeState.h"
#include "repository/TimeControllerRepository.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace core::repository;
using namespace testing;

class GameViewModelTest : public Test
{
public:
    GameViewModelTest() {};
    ~GameViewModelTest() override = default;

protected:
    std::shared_ptr<NiceMock<MockTimeControllerRepository>> m_mockTimeControllerRepository;
    std::unique_ptr<app::ui::viewmodels::GameViewModel> m_gameViewModel;

    void SetUp() override
    {
        m_mockTimeControllerRepository = std::make_shared<NiceMock<MockTimeControllerRepository>>();
        m_gameViewModel = std::make_unique<app::ui::viewmodels::GameViewModel>(m_mockTimeControllerRepository);
    }
};

TEST_F(GameViewModelTest, UpdateTimeControllerCallsRepositoryUpdateTime)
{
    EXPECT_CALL(*m_mockTimeControllerRepository, updateTime()).Times(1);
    m_gameViewModel->updateTimeController();
}

TEST_F(GameViewModelTest, IsGamePausedReturnsRepositoryIsPaused)
{
    EXPECT_CALL(*m_mockTimeControllerRepository, isPaused()).WillOnce(Return(true));
    EXPECT_TRUE(m_gameViewModel->isGamePaused());

    EXPECT_CALL(*m_mockTimeControllerRepository, isPaused()).WillOnce(Return(false));
    EXPECT_FALSE(m_gameViewModel->isGamePaused());
}

TEST_F(GameViewModelTest, TogglePauseCallsRepositoryTogglePause)
{
    EXPECT_CALL(*m_mockTimeControllerRepository, togglePause()).Times(1);
    m_gameViewModel->togglePause();
}