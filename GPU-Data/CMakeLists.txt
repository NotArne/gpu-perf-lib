cmake_minimum_required(VERSION 3.8)
project(GPU_Monitor)

set(CMAKE_CXX_STANDARD 14)

include(cmake/FindLibDRM.txt)

if(${LibDRM_FOUND})
    message("FOUND LibDrm!")
endif()

macro(reference_libdrm target)
    target_include_directories(${target} PRIVATE ${Libdrm_INCLUDE_DIRS})
    target_compile_options(${target} PUBLIC ${Libdrm_DEFINITIONS})
    target_link_libraries(${target} PRIVATE ${Libdrm_LIBRARIES})
endmacro()

find_package(PkgConfig)
pkg_check_modules(LIBDRM_AMDGPU libdrm_amdgpu)

# Check for amdgpu libdrm library
SET(AMDGPU_SRC "")
# Add AMDGPU specific data sources
if(${LIBDRM_AMDGPU_FOUND})
    message("FOUND libdrm-amdgpu!")
    SET(LIBDRM_AMDGPU_LIBRARY  ${LIBDRM_AMDGPU_LIBDIR}/libdrm_amdgpu.so)

    SET(AMDGPU_SRC ${AMDGPU_SRC}
            GPU-Data/amdgpu/AMDGPUHandler.cpp
            GPU-Data/amdgpu/AMDMonitoringData.cpp
            GPU-Data/amdgpu/AMDStaticDeviceData.cpp)
endif()

# Check for cuda library
find_package(CUDA)

SET(NVIDIA_SRC "")
if(${CUDA_FOUND})
    message("FOUND CUDA!")
    SET(NVIDIA_SRC ${NVIDIA_SRC}
            GPU-Data/nvidia/NvidiaHandler.cpp
            GPU-Data/nvidia/NvidiaStaticDeviceData.cpp
            GPU-Data/nvidia/NvidiaHelper.cpp
            GPU-Data/nvidia/NvidiaMonitoringData.cpp)
endif()


# Build GPU data library
add_library(gpu-data STATIC
        GPU-Data/BaseGPUData.cpp
        GPU-Data/CombinedGPUData.cpp
        GPU-Data/ExceptionHandling.cpp
        GPU-Data/GPUScanner.cpp
        ${AMDGPU_SRC} # Add amdgpu specific implementation
        ${NVIDIA_SRC} # Add nvidia specific implementation
        )
reference_libdrm(gpu-data)
target_include_directories(gpu-data PRIVATE gpu-data/include)

if(${LIBDRM_AMDGPU_FOUND}) # Add amdgpu specific implementation
    target_include_directories(gpu-data PRIVATE gpu-data/amdgpu)
    target_link_libraries(gpu-data PRIVATE ${LIBDRM_AMDGPU_LIBRARY})
    target_compile_definitions(gpu-data PUBLIC AMDGPU_FOUND)
endif()

if(${CUDA_FOUND})
    target_include_directories(gpu-data PRIVATE ${CUDA_INCLUDE_DIRS}/nvml.h)
    target_link_libraries(gpu-data PRIVATE /usr/lib/x86_64-linux-gnu/libnvidia-ml.so)
    target_compile_definitions(gpu-data PRIVATE NVIDIA_FOUND)
endif()