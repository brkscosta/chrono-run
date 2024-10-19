file(GLOB_RECURSE APP_SOURCES "*.cpp" "*.h")

target_sources(ChronoRun PRIVATE ${APP_SOURCES})
