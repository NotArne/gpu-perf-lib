cmake_minimum_required(VERSION 3.8)
project(GPU_Monitor)

set(CMAKE_CXX_STANDARD 14)

include(GPU-Data/CMakeLists.txt)

add_executable(GPU_Monitor main.cpp)

target_include_directories(GPU_Monitor PRIVATE ${Libdrm_INCLUDE_DIRS})
target_include_directories(GPU_Monitor PRIVATE gpu-data/include)
target_link_libraries(GPU_Monitor PRIVATE gpu-data)
