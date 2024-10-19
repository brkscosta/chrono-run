cmake_minimum_required(VERSION 3.15)

if(EXISTS "${CMAKE_SOURCE_DIR}/local.cmake")
    include("${CMAKE_SOURCE_DIR}/local.cmake")
    message(STATUS "Including local.cmake")
endif()

set(PROJECT_NAME "ChronoRun")
set(CMAKE_CXX_STANDARD 17)
set(APP_VERSION ${VERSION})
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

include_directories(${CMAKE_BINARY_DIR}/src)

add_executable(${PROJECT_NAME} src/main.cpp)

add_subdirectory(src/app)
add_subdirectory(src/core)
add_subdirectory(src/domain)

target_link_libraries(${PROJECT_NAME} PRIVATE sfml::sfml)

# Clang-tidy
find_program(CLANG_TIDY_EXE NAMES "clang-tidy" "clang-tidy-<version>")
if (CLANG_TIDY_EXE AND CMAKE_BUILD_TYPE STREQUAL "Release")
    set(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY_EXE};-checks=*")
endif ()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_options(-Wall -Wextra -Wpedantic)
    target_compile_options(${PROJECT_NAME} PRIVATE -g)
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

add_compile_definitions(GIT_COMMIT_HASH="${GIT_COMMIT_HASH}")

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug" CACHE STRING
        "Choose the type of build, options are: Debug Release." FORCE)
endif()

configure_file(config.h.in ${CMAKE_BINARY_DIR}/src/config.h)

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "Conan libraries: ${CONAN_LIBS}")
