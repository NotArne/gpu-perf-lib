//
// Created by arne on 23.03.22.
//
#include <libdrm/amdgpu_drm.h>
#include <libdrm/amdgpu.h>
#include <iostream>

#include "AMDMonitoringData.h"
#include "../include/ExceptionHandling.h"

AMDMonitoringData::AMDMonitoringData(amdgpu_device_handle handle) : MonitoringData(VENDOR_AMD_AMDGPU) {
    this->gpuHandle = handle;
}

uint32_t AMDMonitoringData::getTotalGPUWorkload() {
    uint32_t totalWorkload;
    // General GPU load
    int checkError = amdgpu_query_sensor_info(gpuHandle, AMDGPU_INFO_SENSOR_GPU_LOAD,
                             sizeof(uint32_t), &totalWorkload);
    if(checkError != 0) {
        throw GPUDataRetrievingFailureException("Failed to retrieve total GPU workload!", getVendor(), checkError);
    }
    return totalWorkload;
}


uint64_t AMDMonitoringData::getUsedVRAM() {
    uint64_t usedVRAM;
    // Usage of VRAM
    int checkError = amdgpu_query_info(gpuHandle, AMDGPU_INFO_VRAM_USAGE,
                             sizeof(uint64_t), &usedVRAM);
    if(checkError != 0) {
        throw GPUDataRetrievingFailureException("Failed to retrieve used VRAM!", getVendor(), checkError);
    }
    return usedVRAM;
}

uint32_t AMDMonitoringData::getCurrentMemoryClock() {
    uint32_t memoryClock;
    // Memory clock
    int checkError = amdgpu_query_sensor_info(gpuHandle, AMDGPU_INFO_SENSOR_GFX_MCLK,
                             sizeof(uint32_t), &memoryClock);
    if(checkError != 0) {
        throw GPUDataRetrievingFailureException("Failed to retrieve current memory clock!", getVendor(), checkError);
    }
    return memoryClock;
}

uint32_t AMDMonitoringData::getCurrentShaderClock() {
    uint32_t shaderClock;
    // Shader clock
    int checkError = amdgpu_query_sensor_info(gpuHandle, AMDGPU_INFO_SENSOR_GFX_SCLK,
                             sizeof(uint32_t), &shaderClock);
    if(checkError != 0) {
        throw GPUDataRetrievingFailureException("Failed to retrieve current shader clock!", getVendor(), checkError);
    }
    return shaderClock;
}

uint32_t AMDMonitoringData::getChipTemperature() {
    uint32_t chipTemperature;
    // Temperature
    int checkError = amdgpu_query_sensor_info(gpuHandle, AMDGPU_INFO_SENSOR_GPU_TEMP,
                             sizeof(uint32_t), &chipTemperature);
    if(checkError != 0) {
        throw GPUDataRetrievingFailureException("Failed to retrieve current chip temperature!", getVendor(), checkError);
    }
    return chipTemperature;
}

uint32_t AMDMonitoringData::getCurrentPowerConsumption() {
    uint32_t powerConsumption;
    // Power consumption
    int checkError = amdgpu_query_sensor_info(gpuHandle, AMDGPU_INFO_SENSOR_GPU_AVG_POWER,
                             sizeof(uint32_t), &powerConsumption);
    if(checkError != 0) {
        throw GPUDataRetrievingFailureException("Failed to retrieve current power consumption!", getVendor(), checkError);
    }
    return powerConsumption;
}
