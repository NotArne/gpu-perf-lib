cmake_minimum_required(VERSION 3.21)
project(GPU_Monitor)

set(CMAKE_CXX_STANDARD 14)

include(cmake/FindLibDRM.txt)

SET(GCC_COVERAGE_COMPILE_FLAGS "-DHAS_DRMGETDEVICE=1 -DENABLE_AMDGPU=1 -DHAS_AMDGPU_QUERY_SENSOR_INFO=1")
#SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")

#LIBDRM_FOUND
# LIBDRM_INCLUDE_DIR
# LIBDRM_LIBRARIES

if(${LibDRM_FOUND})
    message("FOUND LibDrm!")
endif()
#include_directories(${Libdrm_INCLUDE_DIRS})

include_directories(${LIBDRM_INCLUDE_DIR})
add_executable(GPU_Monitor main.cpp
        GPU-Data/include/MonitoringData.h
        GPU-Data/include/StaticDeviceData.h
        GPU-Data/amdgpu/AMDMonitoringData.cpp
        GPU-Data/amdgpu/AMDMonitoringData.h
        GPU-Data/amdgpu/AMDDeviceData.cpp
        GPU-Data/amdgpu/AMDDeviceData.h
        GPU-Data/include/BaseGPUData.h
        GPU-Data/GPUScanner.cpp
        GPU-Data/include/GPUScanner.h
        GPU-Data/include/SupportedVendors.h GPU-Data/BaseGPUData.cpp GPU-Data/CombinedGPUData.cpp GPU-Data/include/CombinedGPUData.h)

target_compile_options(GPU_Monitor PUBLIC ${Libdrm_DEFINITIONS})

target_link_libraries(GPU_Monitor PRIVATE ${LIBDRM_LIBRARY})
#target_link_libraries(GPU_Monitor PRIVATE )
target_link_libraries(GPU_Monitor PRIVATE /usr/lib/libdrm_amdgpu.so)
message(${LIBDRM_LIBRARY})
#target_link_libraries(GPU_Monitor PRIVATE ${Libdrm_LIBRARIES})