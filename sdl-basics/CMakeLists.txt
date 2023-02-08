cmake_minimum_required(VERSION 3.7.0)
project(trippyscreen VERSION 0.1.0)

include(CTest)
enable_testing()

set(CMAKE_CXX_STANDARD 20)

find_package(SDL2 REQUIRED)
include_directories(SDL2Test ${SDL2_INCLUDE_DIRS})

set(SOURCE_FILES main.cpp app.hpp app.cpp color-code.hpp)

add_executable(trippyscreen ${SOURCE_FILES})
target_link_libraries(trippyscreen ${SDL2_LIBRARIES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
