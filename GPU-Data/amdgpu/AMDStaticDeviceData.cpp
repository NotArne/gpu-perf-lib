//
// Created by arne on 29.03.22.
//

#include <iostream>
#include <amdgpu_drm.h>
#include "AMDStaticDeviceData.h"
#include "../include/ExceptionHandling.h"

AMDStaticDeviceData::AMDStaticDeviceData(amdgpu_device_handle gpuHandle) : StaticDeviceData(VENDOR_AMD_AMDGPU) {
    this->gpuHandle = gpuHandle;
    this->updateData(); // Initialize values automatically
}

void AMDStaticDeviceData::updateData() {
    // GPU name
    marketingName = amdgpu_get_marketing_name(gpuHandle);

    // General GPU information
    struct amdgpu_gpu_info gpuInfo;
    int checkError1 = amdgpu_query_gpu_info(gpuHandle, &gpuInfo);
    if(checkError1 == 0) {
        maxMemoryClock = gpuInfo.max_memory_clk;
        maxShaderClock = gpuInfo.max_engine_clk;
        memoryBitWidth = gpuInfo.vram_bit_width;
        amountOfCUs = gpuInfo.cu_active_number;
        amountOfShaders = 0; //TODO: actual information not found
    }

    // VRAM info
    struct drm_amdgpu_info_vram_gtt vramInfo;
    int checkError2 = amdgpu_query_info(gpuHandle, AMDGPU_INFO_VRAM_GTT,
                      sizeof(vramInfo), &vramInfo);
    if(checkError2 == 0) {
        totalVRAM = vramInfo.vram_size;
    }

    if(checkError1 != 0 || checkError2 != 0) {
        throw GPUDataRetrievingFailureException("Failed to retrieve static GPU information!", getVendor(), (checkError1 == 0) ? checkError2 : checkError1);
        // If both requests failed, one of both errorCodes is returned (I know not perfect)
    }
}

uint64_t AMDStaticDeviceData::getMaxShaderClock() {
    return maxShaderClock;
}

uint64_t AMDStaticDeviceData::getMaxMemoryClock() {
    return maxMemoryClock;
}

uint64_t AMDStaticDeviceData::getTotalVRAM() {
    return totalVRAM;
}

std::string AMDStaticDeviceData::getMarketingName() {
    return marketingName;
}

uint32_t AMDStaticDeviceData::getMemoryBitWidth() {
    return memoryBitWidth;
}

uint32_t AMDStaticDeviceData::getAmountOfShaders() {
    return amountOfShaders;
}

uint32_t AMDStaticDeviceData::getAmountOfComputeUnits() {
    return amountOfCUs;
}

