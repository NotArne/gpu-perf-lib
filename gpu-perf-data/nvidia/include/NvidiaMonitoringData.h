//
// Created by arne on 09.04.22.
//

#ifndef GPU_MONITOR_NVIDIAMONITORINGDATA_H
#define GPU_MONITOR_NVIDIAMONITORINGDATA_H

#include <nvml.h>
#include <cstdint>
#include "../../include/MonitoringData.h"

class NvidiaMonitoringData : public MonitoringData {

private:
    nvmlDevice_t gpuHandle;

public:
    NvidiaMonitoringData(nvmlDevice_t gpuHandle);

    uint32_t getTotalGPUWorkload() override;

    uint64_t getUsedVRAM() override;

    uint32_t getCurrentMemoryClock() override;

    uint32_t getCurrentShaderClock() override;

    uint32_t getChipTemperature() override;

    uint32_t getCurrentPowerConsumption() override;
};

#endif //GPU_MONITOR_NVIDIAMONITORINGDATA_H
