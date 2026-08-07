cmake_minimum_required(VERSION 4.2.1)

enable_language(C CXX)

set(Mlink_Programmer_Src
    ${CMAKE_CURRENT_SOURCE_DIR}/../app/Src/main.c
)

set(Mlink_Programmer_Inc
    ${CMAKE_CURRENT_SOURCE_DIR}/../app/Inc/
    ${CMAKE_CURRENT_SOURCE_DIR}/../SDL-release-3.4.14/include/
)

add_library(app INTERFACE)

target_include_directories(app INTERFACE ${Mlink_Programmer_Inc})

target_sources(${CMAKE_PROJECT_NAME} PRIVATE ${Mlink_Programmer_Src})
