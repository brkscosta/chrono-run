cmake_minimum_required(VERSION 3.15)

if(EXISTS "${CMAKE_SOURCE_DIR}/local.cmake")
    include("${CMAKE_SOURCE_DIR}/local.cmake")
    message(STATUS "Including local.cmake")
endif()

set(PROJECT_NAME "ChronoRun")
set(CMAKE_CXX_STANDARD 17)
set(HAS_GTEST ON)
set(APP_VERSION 0.1.0)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)

project("${PROJECT_NAME}")

execute_process(
    COMMAND git rev-parse --short HEAD
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    OUTPUT_VARIABLE GIT_COMMIT_HASH
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

find_package(SFML 2.5 COMPONENTS system window graphics audio REQUIRED)
find_package(Boost)
find_package(GTest)

include_directories(${CMAKE_BINARY_DIR}/src)

add_executable(${PROJECT_NAME} src/main.cpp)

add_subdirectory(src/app)
add_subdirectory(src/core)
add_subdirectory(src/domain)

if(HAS_GTEST)
  enable_testing()
  add_subdirectory(src/tests)
endif()


# Link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE sfml::sfml boost::boost)

# Clang-tidy
find_program(CLANG_TIDY_EXE NAMES "clang-tidy" "clang-tidy-<version>")
if (CLANG_TIDY_EXE AND CMAKE_BUILD_TYPE STREQUAL "Release")
    set(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY_EXE};-checks=*")
endif()

option(HAS_GTEST "Build with Google Test support" OFF)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_options(-Wall -Wextra -Wpedantic)
    target_compile_options(${PROJECT_NAME} PRIVATE -g)
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    add_compile_options(-O3)
    add_definitions(-DNDEBUG)
endif()

# Symlink compile_commands.json
if (NOT EXISTS ${CMAKE_SOURCE_DIR}/compile_commands.json)
    execute_process(
        COMMAND ${CMAKE_COMMAND} -E create_symlink
            ${CMAKE_BINARY_DIR}/compile_commands.json
            ${CMAKE_SOURCE_DIR}/compile_commands.json
    )
    message(STATUS "Symlinked compile_commands.json")
endif()

# Define preprocessor definitions
add_definitions(-DGIT_COMMIT_HASH="${GIT_COMMIT_HASH}" -DVERSION="${VERSION}")

# Install rules
if (WIN32)
    set(CMAKE_INSTALL_PREFIX "C:/Program Files/${PROJECT_NAME}/")
    install(TARGETS ${PROJECT_NAME}
        RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}
        LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
    )
    install(DIRECTORY assets/ DESTINATION ${CMAKE_INSTALL_PREFIX}/assets)
    add_definitions(-DASSETS_PATH="${CMAKE_INSTALL_PREFIX}/assets/")
    add_definitions(-DSPRITE_ASSETS_PATH="${CMAKE_INSTALL_PREFIX}/assets/sprites/")
    add_definitions(-DSOUNDS_ASSETS_PATH="${CMAKE_INSTALL_PREFIX}/assets/sprites/sounds/")
elseif (UNIX)
    set(CMAKE_INSTALL_PREFIX "$ENV{HOME}/.local/")
    install(TARGETS ${PROJECT_NAME}
        RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin/${PROJECT_NAME}
        LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/${PROJECT_NAME}
    )
    install(DIRECTORY assets/ DESTINATION ${CMAKE_INSTALL_PREFIX}share/${PROJECT_NAME}/assets)
    add_definitions(-DASSETS_PATH="${CMAKE_INSTALL_PREFIX}share/${PROJECT_NAME}/assets/")
    add_definitions(-DSPRITE_ASSETS_PATH="${CMAKE_INSTALL_PREFIX}share/${PROJECT_NAME}/assets/sprites/")
    add_definitions(-DSOUNDS_ASSETS_PATH="${CMAKE_INSTALL_PREFIX}share/${PROJECT_NAME}/assets/sounds/")
endif()
message(STATUS "Installation directory: ${CMAKE_INSTALL_PREFIX}")

# Configure file
configure_file(config.h.in ${CMAKE_BINARY_DIR}/src/config.h)

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

# Post-build command to copy assets
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:${PROJECT_NAME}>/assets
)
