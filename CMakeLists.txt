cmake_minimum_required(VERSION 4.2.1)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

set(CMAKE_PROJECT_NAME Jyouhou_kadai)

set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

project(${CMAKE_PROJECT_NAME})
message("Build type: " ${CMAKE_BUILD_TYPE})

enable_language(C CXX)

add_executable(${CMAKE_PROJECT_NAME})
include(FetchContent)
FetchContent_Declare(
    SDL3
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG        release-3.4.16
    GIT_PROGRESS TRUE
)

FetchContent_Declare(
    SDL3_image
    GIT_REPOSITORY https://github.com/libsdl-org/SDL_image.git
    GIT_TAG        release-3.4.6
    GIT_PROGRESS TRUE
)
set(BUILD_SHARED_LIBS ON CACHE INTERNAL "BUILD Shared libraries")

FetchContent_MakeAvailable(SDL3 SDL3_image)

add_subdirectory(toolchain)


target_link_directories(${CMAKE_PROJECT_NAME} PRIVATE)

target_sources(${CMAKE_PROJECT_NAME} PRIVATE)

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE)

target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE)

list(REMOVE_ITEM CMAKE_C_IMPLICIT_LINK_LIBRARIES ob)
target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC
    app
    SDL3::SDL3
    SDL3_image::SDL3_image
)
if(WIN32)
    add_custom_command(
        TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_RUNTIME_DLLS:${CMAKE_PROJECT_NAME}>
            $<TARGET_FILE_DIR:${CMAKE_PROJECT_NAME}>
        COMMAND_EXPAND_LISTS
    )
endif()