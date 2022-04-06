cmake_minimum_required(VERSION 3.21)
project(GPU_Monitor)

set(CMAKE_CXX_STANDARD 14)

include(cmake/FindLibDRM.txt)

if(${LibDRM_FOUND})
    message("FOUND LibDrm!")
endif()

message(${Libdrm_INCLUDE_DIRS})
add_executable(GPU_Monitor main.cpp
        GPU-Data/include/MonitoringData.h
        GPU-Data/include/StaticDeviceData.h
        GPU-Data/amdgpu/AMDMonitoringData.cpp
        GPU-Data/amdgpu/AMDMonitoringData.h
        GPU-Data/amdgpu/AMDStaticDeviceData.cpp
        GPU-Data/amdgpu/AMDStaticDeviceData.h
        GPU-Data/include/BaseGPUData.h
        GPU-Data/GPUScanner.cpp
        GPU-Data/include/GPUScanner.h
        GPU-Data/include/SupportedVendors.h GPU-Data/BaseGPUData.cpp GPU-Data/CombinedGPUData.cpp GPU-Data/include/CombinedGPUData.h GPU-Data/include/GPUHandler.h GPU-Data/amdgpu/AMDGPUHandler.cpp GPU-Data/amdgpu/AMDGPUHandler.h GPU-Data/include/ExceptionHandling.h GPU-Data/ExceptionHandling.cpp)

target_include_directories(GPU_Monitor PRIVATE ${Libdrm_INCLUDE_DIRS})

target_compile_options(GPU_Monitor PUBLIC ${Libdrm_DEFINITIONS})

target_link_libraries(GPU_Monitor PRIVATE ${Libdrm_LIBRARIES})
target_link_libraries(GPU_Monitor PRIVATE /usr/lib/libdrm_amdgpu.so)

message(${Libdrm_LIBRARIES})