#include "ui/player/PlayerEventImpl.h"

#include "include/IInputManager.h"
#include "include/IPlayerEvents.h"
#include "mocks/internalsources/MockPlayerEvents.h"
#include <SFML/Window/Keyboard.hpp>

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <memory>

using namespace app::ui;
using namespace testing;

class PlayerEventImplTest : public Test
{
protected:
    std::shared_ptr<events::MockPlayerEvents> m_mockPlayerEvents;
    std::unique_ptr<events::IInputManager> m_playerEventImpl;

    void SetUp() override
    {
        m_mockPlayerEvents = std::make_shared<events::MockPlayerEvents>();
        m_playerEventImpl = std::make_unique<views::PlayerEventImpl>(m_mockPlayerEvents);
    }
};

TEST_F(PlayerEventImplTest, onKeyPressed_WKey_CallsOnMoveWithCorrectParameters)
{
    EXPECT_CALL(*m_mockPlayerEvents, onMove(0.f, -1.f));
    m_playerEventImpl->onKeyPressed(sf::Keyboard::W);
}

TEST_F(PlayerEventImplTest, onKeyPressed_SKey_CallsOnMoveWithCorrectParameters)
{
    EXPECT_CALL(*m_mockPlayerEvents, onMove(0.f, 1.f));
    m_playerEventImpl->onKeyPressed(sf::Keyboard::S);
}

TEST_F(PlayerEventImplTest, onKeyPressed_AKey_CallsOnMoveWithCorrectParameters)
{
    EXPECT_CALL(*m_mockPlayerEvents, onMove(-1.f, 0.f));
    m_playerEventImpl->onKeyPressed(sf::Keyboard::A);
}

TEST_F(PlayerEventImplTest, onKeyPressed_DKey_CallsOnMoveWithCorrectParameters)
{
    EXPECT_CALL(*m_mockPlayerEvents, onMove(1.f, 0.f));
    m_playerEventImpl->onKeyPressed(sf::Keyboard::D);
}

TEST_F(PlayerEventImplTest, onKeyPressed_SpaceKey_CallsOnAttackWeak)
{
    EXPECT_CALL(*m_mockPlayerEvents, onAttackWeak());
    m_playerEventImpl->onKeyPressed(sf::Keyboard::Space);
}

TEST_F(PlayerEventImplTest, onKeyReleased_MovementKey_CallsOnStopMove)
{
    EXPECT_CALL(*m_mockPlayerEvents, onStopMove()).Times(4);
    m_playerEventImpl->onKeyReleased(sf::Keyboard::W);
    m_playerEventImpl->onKeyReleased(sf::Keyboard::S);
    m_playerEventImpl->onKeyReleased(sf::Keyboard::A);
    m_playerEventImpl->onKeyReleased(sf::Keyboard::D);
}

TEST_F(PlayerEventImplTest, onKeyReleased_NonMovementKey_DoesNotCallOnStopMove)
{
    EXPECT_CALL(*m_mockPlayerEvents, onStopMove()).Times(0);
    m_playerEventImpl->onKeyReleased(sf::Keyboard::Space);
}