cmake_minimum_required(VERSION 3.25.0)
project(SDLIntro VERSION 0.1.0 LANGUAGES C CXX)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/source/*.hpp
)

add_executable(${PROJECT_NAME} ${SOURCES} main.cpp)

add_subdirectory(vendor/SDL EXCLUDE_FROM_ALL)

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/source/
    SDL3::SDL3
)

target_link_libraries(${PROJECT_NAME} PUBLIC SDL3::SDL3)
