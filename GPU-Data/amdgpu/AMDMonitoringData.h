//
// Created by arne on 23.03.22.
//

#ifndef GPU_MONITOR_AMDMONITORINGDATA_H
#define GPU_MONITOR_AMDMONITORINGDATA_H

#include <libdrm/amdgpu.h>
#include "../include/MonitoringData.h"

class AMDMonitoringData : MonitoringData{
private:
    amdgpu_device_handle gpuHandle;

public:
    AMDMonitoringData(amdgpu_device_handle handle);
    int getTotalGPUWorkload() override;
    void updateData() override;
};


#endif //GPU_MONITOR_AMDMONITORINGDATA_H
