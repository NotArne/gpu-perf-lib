cmake_minimum_required(VERSION 3.8)
project(GPU_Monitor)

include(cmake/FindLibDRM.txt)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(gpu-perf-data)

add_executable(GPU_Monitor examples/main.cpp)

target_include_directories(GPU_Monitor PRIVATE ${Libdrm_INCLUDE_DIRS})
target_include_directories(GPU_Monitor PRIVATE ../gpu-perf-data/include)
target_link_libraries(GPU_Monitor PRIVATE gpu-perf-data)
