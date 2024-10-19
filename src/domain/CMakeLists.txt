file(GLOB_RECURSE DOMAIN_SOURCES "*.cpp" "*.h")

target_sources(ChronoRun PRIVATE ${DOMAIN_SOURCES})
