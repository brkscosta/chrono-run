file(GLOB_RECURSE CORE_SOURCES "*.cpp" "*.h")

target_sources(ChronoRun PRIVATE ${CORE_SOURCES})
