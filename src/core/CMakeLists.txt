file(GLOB_RECURSE CORE_SOURCES "*.cpp" "*.h")
target_sources(ChronoRun PRIVATE ${CORE_SOURCES})

target_include_directories(ChronoRun PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/repository
  ${CMAKE_CURRENT_SOURCE_DIR}/utils
  ${CMAKE_CURRENT_SOURCE_DIR}/entities
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)
