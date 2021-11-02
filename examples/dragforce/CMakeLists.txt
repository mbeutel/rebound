
# CMake build script for REBOUND
# drag force example


cmake_minimum_required(VERSION 3.20)

project(rebound-examples-dragforce
    LANGUAGES C
)

find_package(Threads REQUIRED)
find_package(pthreads REQUIRED)
find_package(rebound REQUIRED)

add_executable(dragforce
    problem.c
)
target_link_libraries(dragforce
    PRIVATE
        rebound::rebound
)
