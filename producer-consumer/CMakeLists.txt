cmake_minimum_required(VERSION 3.0.0)
project(producer-consumer VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(producer-consumer main.c)

target_link_libraries(producer-consumer PRIVATE pthread)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
