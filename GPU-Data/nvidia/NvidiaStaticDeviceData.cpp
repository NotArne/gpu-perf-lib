//
// Created by arne on 09.04.22.
//

#include <iostream>
#include "include/NvidiaStaticDeviceData.h"
#include "include/NvidiaHelper.h"
#include "../include/ExceptionHandling.h"

NvidiaStaticDeviceData::NvidiaStaticDeviceData(nvmlDevice_t gpuHandle) : StaticDeviceData(Vendor::VENDOR_NVIDIA_CS) {
    this->gpuHandle = gpuHandle;
    this->updateData();
}

void NvidiaStaticDeviceData::updateData() {
    // Fetch GPU marketing name
    int MAX_LENGTH = 64; // Nvidia says, it will not exceed 64
    char *gpuNameRaw = new char[MAX_LENGTH];

    hasMarketingName = nvmlDeviceGetName(gpuHandle, gpuNameRaw, MAX_LENGTH);

    std::string gpuName(gpuNameRaw);
    delete[] gpuNameRaw;
    if (hasMarketingName == NVML_SUCCESS) {
        marketingName = gpuName;
    }

    // Fetch max memory clock
    unsigned int memoryCount = 100;
    unsigned int *memoryClocks = new unsigned int[memoryCount];
    nvmlReturn_enum maxMemoryClockRet = nvmlDeviceGetSupportedMemoryClocks(gpuHandle, &memoryCount, memoryClocks);

    if (maxMemoryClockRet == NVML_ERROR_INSUFFICIENT_SIZE) { // If initial size is to small, try again with new value set
        delete [] memoryClocks;
        memoryClocks = new unsigned int [memoryCount];
        maxMemoryClockRet = nvmlDeviceGetSupportedMemoryClocks(gpuHandle, &memoryCount, memoryClocks);
    }
    hasMaxMemoryClock = maxMemoryClockRet;
    if (hasMaxMemoryClock == NVML_SUCCESS) {
        for(unsigned int i = 0; i < memoryCount; i++) {
            if(memoryClocks[i] > maxMemoryClock) {
                maxMemoryClock = memoryClocks[i];
            }
        }
    }
    delete [] memoryClocks;

    if(hasMaxMemoryClock == NVML_SUCCESS) { // If memory clock not found, graphics clock can not be loaded!
        // Fetch max shader clock
        unsigned int shaderCount = 100;
        unsigned int *shaderClocks = new unsigned int[shaderCount];
        nvmlReturn_enum maxShaderClocksRet = nvmlDeviceGetSupportedGraphicsClocks(gpuHandle, maxMemoryClock,
                                                                                  &shaderCount, shaderClocks);
        std::cout << nvmlErrorString(maxShaderClocksRet) << std::endl;
        if (maxShaderClocksRet ==
            NVML_ERROR_INSUFFICIENT_SIZE) { // If initial size is to small, try again with new value set
            delete[] shaderClocks;
            shaderClocks = new unsigned int[shaderCount];
            maxShaderClocksRet = nvmlDeviceGetSupportedGraphicsClocks(gpuHandle, maxMemoryClock, &shaderCount,
                                                                      shaderClocks);
        }
        hasMaxShaderClock = maxShaderClocksRet;
        if (hasMaxShaderClock == NVML_SUCCESS) {
            for (unsigned int i = 0; i < shaderCount; i++) {
                if (shaderClocks[i] > maxShaderClock) {
                    maxShaderClock = shaderClocks[i];
                }
            }
        }
        delete[] shaderClocks;
    } else {
        hasMaxShaderClock = NVML_ERROR_NOT_SUPPORTED;
    }

    // Fetch VRAM size
    nvmlMemory_t vramQuery;
    hasTotalVRAM = nvmlDeviceGetMemoryInfo(gpuHandle, &vramQuery);
    if(hasTotalVRAM == NVML_SUCCESS) {
        totalVRAM = vramQuery.total;
    }

    // Not yet supported by NVML
    hasAmountOfShaders = NVML_ERROR_NOT_SUPPORTED;
    hasAmountOfCUs = NVML_ERROR_NOT_SUPPORTED;
    hasMemoryBitWidth = NVML_ERROR_NOT_SUPPORTED;
}

std::string NvidiaStaticDeviceData::getMarketingName() {
    NvidiaHelper::throwConcreteError(hasMarketingName, "MarketingName");
    return marketingName;
}

uint64_t NvidiaStaticDeviceData::getMaxShaderClock() {
    NvidiaHelper::throwConcreteError(hasMaxShaderClock, "MaxShaderClock");
    return maxShaderClock;
}

uint64_t NvidiaStaticDeviceData::getMaxMemoryClock() {
    NvidiaHelper::throwConcreteError(hasMaxMemoryClock, "MaxMemoryClock");
    return maxMemoryClock;
}

uint64_t NvidiaStaticDeviceData::getTotalVRAM() {
    NvidiaHelper::throwConcreteError(hasTotalVRAM, "TotalVRAM");
    return totalVRAM;
}

uint32_t NvidiaStaticDeviceData::getMemoryBitWidth() {
    NvidiaHelper::throwConcreteError(hasMemoryBitWidth, "MemoryBitWidth");
    return memoryBitWidth;
}

uint32_t NvidiaStaticDeviceData::getAmountOfShaders() {
    NvidiaHelper::throwConcreteError(hasAmountOfShaders, "AmountOfShaders");
    return amountOfShaders;
}

uint32_t NvidiaStaticDeviceData::getAmountOfComputeUnits() {
    NvidiaHelper::throwConcreteError(hasAmountOfCUs, "AmountOfCUs");
    return amountOfCUs;
}