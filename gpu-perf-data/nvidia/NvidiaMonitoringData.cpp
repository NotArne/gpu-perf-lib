//
// Created by arne on 09.04.22.
//

#include "include/NvidiaMonitoringData.h"
#include "include/NvidiaHelper.h"

NvidiaMonitoringData::NvidiaMonitoringData(nvmlDevice_t gpuHandle) : MonitoringData(VENDOR_NVIDIA_CS){
    this->gpuHandle = gpuHandle;
}

uint32_t NvidiaMonitoringData::getTotalGPUWorkload() {
    nvmlUtilization_t deviceUtilization;
    nvmlReturn_enum ret = nvmlDeviceGetUtilizationRates(gpuHandle, &deviceUtilization);
    NvidiaHelper::throwConcreteError(ret, "TotalGPUWorkload");
    return deviceUtilization.gpu;
}

uint64_t NvidiaMonitoringData::getUsedVRAM() {
    nvmlMemory_t vramQuery;
    nvmlReturn_enum ret = nvmlDeviceGetMemoryInfo(gpuHandle, &vramQuery);
    NvidiaHelper::throwConcreteError(ret, "UsedVRAM");
    return vramQuery.used;
}

uint32_t NvidiaMonitoringData::getCurrentMemoryClock() {
    unsigned int memoryClockMHZ;
    nvmlReturn_enum ret = nvmlDeviceGetClockInfo(gpuHandle, NVML_CLOCK_MEM, &memoryClockMHZ);
    NvidiaHelper::throwConcreteError(ret, "MemoryClock");
    return memoryClockMHZ;
}

uint32_t NvidiaMonitoringData::getCurrentShaderClock() {
    unsigned int shaderClockMHZ;
    nvmlReturn_enum ret = nvmlDeviceGetClockInfo(gpuHandle, NVML_CLOCK_GRAPHICS, &shaderClockMHZ);
    NvidiaHelper::throwConcreteError(ret, "ShaderClock");
    return shaderClockMHZ;
}

uint32_t NvidiaMonitoringData::getChipTemperature() {
    unsigned int chipTemperature;
    nvmlReturn_enum ret = nvmlDeviceGetTemperature(gpuHandle, NVML_TEMPERATURE_GPU, &chipTemperature);
    NvidiaHelper::throwConcreteError(ret, "ChipTemperature");
    return chipTemperature;
}

uint32_t NvidiaMonitoringData::getCurrentPowerConsumption() {
    unsigned int powerUseage;
    nvmlReturn_enum ret = nvmlDeviceGetPowerUsage(gpuHandle, &powerUseage);
    NvidiaHelper::throwConcreteError(ret, "ChipTemperature");
    return powerUseage;
}
