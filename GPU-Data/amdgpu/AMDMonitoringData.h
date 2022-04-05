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

    int totalWorkload;
    long usedVRAM;
    int memoryClock;
    int shaderClock;
    int memoryTemperature;
    int chipTemperature;
    int powerConsumption;

public:
    AMDMonitoringData(amdgpu_device_handle handle);

    int getTotalGPUWorkload() override;

    void updateData() override;

    long getUsedVRAM() override;

    int getCurrentMemoryClock() override;

    int getCurrentShaderClock() override;

    int getChipTemperature() override;

    int getCurrentPowerConsumption() override;
};


#endif //GPU_MONITOR_AMDMONITORINGDATA_H
