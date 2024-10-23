#include "ui/player/PlayerViewModel.h"

#include "mocks/internalsources/MockPlayer.h"
#include "mocks/internalsources/MockTimeControllerRepository.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace app::ui;
using namespace testing;

class PlayerViewModelTest : public Test
{
protected:
    std::shared_ptr<core::entities::MockPlayer> mockPlayer;
    std::shared_ptr<core::repository::MockTimeControllerRepository> mockTimeControllerRepository;
    std::unique_ptr<viewmodels::PlayerViewModel> playerViewModel;

    void SetUp() override
    {
        mockPlayer = std::make_shared<core::entities::MockPlayer>();
        mockTimeControllerRepository = std::make_shared<core::repository::MockTimeControllerRepository>();
        playerViewModel = std::make_unique<viewmodels::PlayerViewModel>(mockPlayer, mockTimeControllerRepository);
    }
};

TEST_F(PlayerViewModelTest, GetPlayerState)
{
    core::entities::PlayerState expectedState = core::entities::PlayerState::Idle;
    EXPECT_CALL(*mockPlayer, getState()).WillOnce(Return(expectedState));

    auto state = playerViewModel->getPlayerState();

    EXPECT_EQ(state, expectedState);
}

TEST_F(PlayerViewModelTest, SetPlayerState)
{
    core::entities::PlayerState newState = core::entities::PlayerState::Walking;
    EXPECT_CALL(*mockPlayer, setState(newState)).Times(1);

    playerViewModel->setState(newState);
}

TEST_F(PlayerViewModelTest, GetPlayerPosition)
{
    float expectedX = 10.0f;
    float expectedY = 20.0f;
    EXPECT_CALL(*mockPlayer, getX()).WillOnce(Return(expectedX));
    EXPECT_CALL(*mockPlayer, getY()).WillOnce(Return(expectedY));

    auto position = playerViewModel->getPlayerPosition();

    EXPECT_EQ(position.x, expectedX);
    EXPECT_EQ(position.y, expectedY);
}

TEST_F(PlayerViewModelTest, SetPlayerPosition)
{
    float x = 5.0f;
    float y = 10.0f;
    float speed = 2.0f;
    float deltaTime = 0.5f;
    float initialX = 1.0f;
    float initialY = 1.0f;

    EXPECT_CALL(*mockPlayer, getSpeed()).WillOnce(Return(speed));
    EXPECT_CALL(*mockTimeControllerRepository, getDeltaTime()).WillOnce(Return(deltaTime));
    EXPECT_CALL(*mockPlayer, getX()).WillOnce(Return(initialX));
    EXPECT_CALL(*mockPlayer, getY()).WillOnce(Return(initialY));
    EXPECT_CALL(*mockPlayer, setX(initialX + x * speed * deltaTime)).Times(1);
    EXPECT_CALL(*mockPlayer, setY(initialY + y * speed * deltaTime)).Times(1);

    playerViewModel->setPlayerPosition(x, y);
}

TEST_F(PlayerViewModelTest, GetLife)
{
    int expectedLife = 100;
    EXPECT_CALL(*mockPlayer, getLife()).WillOnce(Return(expectedLife));

    auto life = playerViewModel->getLife();

    EXPECT_EQ(life, expectedLife);
}

TEST_F(PlayerViewModelTest, SetLife)
{
    int newLife = 80;
    EXPECT_CALL(*mockPlayer, setLife(newLife)).Times(1);

    playerViewModel->setLife(newLife);
}

TEST_F(PlayerViewModelTest, GetDeltaTime)
{
    float expectedDeltaTime = 0.016f;
    EXPECT_CALL(*mockTimeControllerRepository, getDeltaTime()).WillOnce(Return(expectedDeltaTime));

    auto deltaTime = playerViewModel->getDeltaTime();

    EXPECT_EQ(deltaTime, expectedDeltaTime);
}