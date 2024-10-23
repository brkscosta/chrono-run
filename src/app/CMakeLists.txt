file(GLOB_RECURSE APP_SOURCES "*.cpp" "*.h")

target_sources(ChronoRun PRIVATE ${APP_SOURCES})

target_include_directories(ChronoRun PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/ui
  ${CMAKE_CURRENT_SOURCE_DIR}/di
  ${CMAKE_CURRENT_SOURCE_DIR}/utils
)