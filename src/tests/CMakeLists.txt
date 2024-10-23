include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/mocks/external
  ${CMAKE_CURRENT_SOURCE_DIR}/mocks/internalsources
  ${CMAKE_SOURCE_DIR}/src/app/
  ${CMAKE_SOURCE_DIR}/src/app/ui/
  ${CMAKE_SOURCE_DIR}/src/app/utils/
  ${CMAKE_SOURCE_DIR}/src/app/ui/engine/
  ${CMAKE_SOURCE_DIR}/src/app/include
  ${CMAKE_SOURCE_DIR}/src/core/
  ${CMAKE_SOURCE_DIR}/src/core/repository/
  ${CMAKE_SOURCE_DIR}/src/core/entities/
  ${CMAKE_SOURCE_DIR}/src/core/utils/
  ${CMAKE_SOURCE_DIR}/src/core/include
  ${CMAKE_SOURCE_DIR}/src/domain/
  ${CMAKE_SOURCE_DIR}/src/domain/usecases/
)

SET(GTEST_SRCS
  MainTest.cpp

  # Test sources
  ${CMAKE_CURRENT_SOURCE_DIR}/ui/game/GameViewModelTest.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ui/game/GameViewTest.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ui/player/PlayerEventImplTest.cpp

  # Target sources
  ${CMAKE_SOURCE_DIR}/src/app/ui/game/GameViewModel.cpp
  ${CMAKE_SOURCE_DIR}/src/app/ui/game/GameView.cpp
  ${CMAKE_SOURCE_DIR}/src/core/repository/TimeControllerRepository.cpp
  ${CMAKE_SOURCE_DIR}/src/core/entities/TimeState.cpp
  ${CMAKE_SOURCE_DIR}/src/app/ui/player/PlayerEventImpl.cpp
)

add_executable(${PROJECT_NAME}Test ${GTEST_SRCS})

add_test(${PROJECT_NAME}Test ${PROJECT_NAME}Test)

add_custom_target(run_tests COMMAND ${PROJECT_NAME}Test)

target_link_libraries(${PROJECT_NAME}Test gtest::gtest sfml::sfml boost::boost)