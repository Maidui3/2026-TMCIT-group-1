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

add_subdirectory(toolchain)
add_subdirectory(SDL-release-3.4.14)
add_subdirectory(SDL_image-release-3.4.4)


target_link_directories(${CMAKE_PROJECT_NAME} PRIVATE)

target_sources(${CMAKE_PROJECT_NAME} PRIVATE)

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE)

target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE)

list(REMOVE_ITEM CMAKE_C_IMPLICIT_LINK_LIBRARIES ob)

target_link_libraries(${CMAKE_PROJECT_NAME}
    app
    SDL3::SDL3
    SDL3_image::SDL3_image
)
