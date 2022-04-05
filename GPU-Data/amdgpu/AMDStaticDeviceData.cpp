//
// Created by arne on 29.03.22.
//

#include <iostream>
#include <amdgpu_drm.h>
#include "AMDStaticDeviceData.h"

AMDStaticDeviceData::AMDStaticDeviceData(amdgpu_device_handle gpuHandle) : StaticDeviceData(VENDOR_AMD) {
    this->gpuHandle = gpuHandle;
    this->updateData(); // Initialize values automatically
}

void AMDStaticDeviceData::updateData() {
    marketingName = amdgpu_get_marketing_name(gpuHandle);
    struct amdgpu_gpu_info gpuInfo;
    int checkError1 = amdgpu_query_gpu_info(gpuHandle, &gpuInfo);
    maxMemoryClock = gpuInfo.max_memory_clk;
    maxShaderClock = gpuInfo.max_engine_clk;
    memoryBitWidth = gpuInfo.vram_bit_width;
    amountOfCUs = gpuInfo.cu_active_number;
    amountOfShaders = -1; //TODO actual information not found

    struct drm_amdgpu_info_vram_gtt vramInfo;
    int checkError2 = amdgpu_query_info(gpuHandle, AMDGPU_INFO_VRAM_GTT,
                      sizeof(vramInfo), &vramInfo);
    totalVRAM = vramInfo.vram_size;

}

int AMDStaticDeviceData::getMaxShaderClock() {
    return maxShaderClock;
}

int AMDStaticDeviceData::getMaxMemoryClock() {
    return maxMemoryClock;
}

long AMDStaticDeviceData::getTotalVRAM() {
    return totalVRAM;
}

std::string AMDStaticDeviceData::getMarketingName() {
    return marketingName;
}

int AMDStaticDeviceData::getMaxMemoryBitWidth() {
    return memoryBitWidth;
}

int AMDStaticDeviceData::getAmountOfShaders() {
    return amountOfShaders;
}

int AMDStaticDeviceData::getAmountOfComputeUnits() {
    return amountOfCUs;
}
