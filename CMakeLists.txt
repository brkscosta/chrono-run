cmake_minimum_required(VERSION 3.15)

set(PROJECT_NAME "ChronoRun")
set(APP_VERSION 0.1.0)
project("${PROJECT_NAME}" VERSION ${APP_VERSION} LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(HAS_GTEST "Build with Google Test support" OFF)

if(EXISTS "${CMAKE_SOURCE_DIR}/local.cmake")
    include("${CMAKE_SOURCE_DIR}/local.cmake")
    message(STATUS "Including local.cmake")
endif()

execute_process(
    COMMAND git rev-parse --short HEAD
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    OUTPUT_VARIABLE GIT_COMMIT_HASH
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

include_directories(${CMAKE_BINARY_DIR}/src)
add_executable(${PROJECT_NAME} src/main.cpp)

find_package(SFML 2.5 COMPONENTS system window graphics audio REQUIRED)
find_package(Boost)

add_subdirectory(src/app)
add_subdirectory(src/core)
add_subdirectory(src/domain)

if(HAS_GTEST)
    find_package(GTest)
    enable_testing()
    add_subdirectory(src/tests)
    message(STATUS "Building with tests")
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE sfml::sfml boost::boost)

if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4 /WX)
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /O2")
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
else()
    if (CMAKE_BUILD_TYPE STREQUAL "Release")
        find_program(CLANG_TIDY_EXE NAMES "clang-tidy")
        if (CLANG_TIDY_EXE)
            set(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY_EXE};-checks=*")
        endif()
    endif()
    if (CMAKE_BUILD_TYPE STREQUAL "Debug")
        add_compile_options(-Wall -Wextra -Wpedantic)
        target_compile_options(${PROJECT_NAME} PRIVATE -g)
    else()
        add_compile_options(-O3)
        add_definitions(-DNDEBUG)
    endif()
endif()

if (WIN32)
    set(CMAKE_INSTALL_PREFIX "C:/Program Files/${PROJECT_NAME}")
    set(ASSETS_PATH "${CMAKE_INSTALL_PREFIX}/assets")
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD 
        COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_SOURCE_DIR}/assets" "$<TARGET_FILE_DIR:${PROJECT_NAME}>/assets"
    )
elseif (UNIX)
    set(CMAKE_INSTALL_PREFIX "$ENV{HOME}/.local")
    set(ASSETS_PATH "${CMAKE_INSTALL_PREFIX}/share/${PROJECT_NAME}/assets")
    if (NOT EXISTS ${CMAKE_SOURCE_DIR}/compile_commands.json)
        execute_process(
            COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_BINARY_DIR}/compile_commands.json ${CMAKE_SOURCE_DIR}/compile_commands.json
        )
        message(STATUS "Symlinked compile_commands.json")
    endif()
endif()

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(ASSETS_PATH "${CMAKE_SOURCE_DIR}/assets")
else()
    set(ASSETS_PATH "${CMAKE_INSTALL_PREFIX}/share/${PROJECT_NAME}/assets")
endif()

set(SOUNDS_ASSETS_PATH "${ASSETS_PATH}/sounds/")
set(SPRITES_ASSETS_PATH "${ASSETS_PATH}/sprites/")
set(RUNTIME_PATH "${CMAKE_INSTALL_PREFIX}/bin/${PROJECT_NAME}")
set(LIB_PATH "${CMAKE_INSTALL_PREFIX}/lib/${PROJECT_NAME}")

install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION "${RUNTIME_PATH}"
    LIBRARY DESTINATION "${LIB_PATH}"
)
install(DIRECTORY assets/ DESTINATION ${ASSETS_PATH})

add_definitions(-DGIT_COMMIT_HASH="${GIT_COMMIT_HASH}")

configure_file(config.h.in ${CMAKE_BINARY_DIR}/src/config.h)

message(STATUS "Installation directory: ${CMAKE_INSTALL_PREFIX}")
message(STATUS "Runtime path: ${RUNTIME_PATH}")
message(STATUS "Lib path: ${LIB_PATH}")
message(STATUS "ASSETS_PATH: ${ASSETS_PATH}")
message(STATUS "SPRITES_ASSETS_PATH: ${SPRITES_ASSETS_PATH}")
message(STATUS "SOUNDS_ASSETS_PATH: ${SOUNDS_ASSETS_PATH}")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "Git commit hash: ${GIT_COMMIT_HASH}")
message(STATUS "App version: ${APP_VERSION}")