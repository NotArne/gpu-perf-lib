//
// Created by arne on 23.03.22.
//

#ifndef GPU_MONITOR_AMDMONITORINGDATA_H
#define GPU_MONITOR_AMDMONITORINGDATA_H

#include <libdrm/amdgpu.h>
#include "../include/MonitoringData.h"

class AMDMonitoringData : public MonitoringData {
private:
    amdgpu_device_handle gpuHandle;

public:
    AMDMonitoringData(amdgpu_device_handle handle);

    uint32_t getTotalGPUWorkload() override;

    uint64_t getUsedVRAM() override;

    uint32_t getCurrentMemoryClock() override;

    uint32_t getCurrentShaderClock() override;

    uint32_t getChipTemperature() override;

    uint32_t getCurrentPowerConsumption() override;
};


#endif //GPU_MONITOR_AMDMONITORINGDATA_H
