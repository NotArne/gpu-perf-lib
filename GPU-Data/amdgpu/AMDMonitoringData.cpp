//
// Created by arne on 23.03.22.
//
#include <libdrm/amdgpu_drm.h>
#include <libdrm/amdgpu.h>
#include <iostream>

#include "AMDMonitoringData.h"

AMDMonitoringData::AMDMonitoringData(amdgpu_device_handle handle) : MonitoringData(VENDOR_AMD) {
    this->gpuHandle = handle;
    this->updateData();
}

void AMDMonitoringData::updateData() {
    // Temperature
    amdgpu_query_sensor_info(gpuHandle, AMDGPU_INFO_SENSOR_GPU_TEMP,
                             sizeof(uint32_t), &chipTemperature);

    // Power consumption
    amdgpu_query_sensor_info(gpuHandle, AMDGPU_INFO_SENSOR_GPU_AVG_POWER,
                             sizeof(uint32_t), &powerConsumption);

    // Shader clock
    amdgpu_query_sensor_info(gpuHandle, AMDGPU_INFO_SENSOR_GFX_SCLK,
                             sizeof(uint32_t), &shaderClock);

    // Memory clock
    amdgpu_query_sensor_info(gpuHandle, AMDGPU_INFO_SENSOR_GFX_MCLK,
                             sizeof(uint32_t), &memoryClock);

    // General GPU load
    amdgpu_query_sensor_info(gpuHandle, AMDGPU_INFO_SENSOR_GPU_LOAD,
                             sizeof(uint32_t), &totalWorkload);

    // Usage of VRAM
    amdgpu_query_sensor_info(gpuHandle, AMDGPU_INFO_VRAM_USAGE,
                             sizeof(uint32_t), &usedVRAM);
}

int AMDMonitoringData::getTotalGPUWorkload() {
    return totalWorkload;
}


long AMDMonitoringData::getUsedVRAM() {
    return usedVRAM;
}

int AMDMonitoringData::getCurrentMemoryClock() {
    return memoryClock;
}

int AMDMonitoringData::getCurrentShaderClock() {
    return shaderClock;
}

int AMDMonitoringData::getChipTemperature() {
    return chipTemperature;
}

int AMDMonitoringData::getCurrentPowerConsumption() {
    return powerConsumption;
}
