//
// Created by arne on 04.04.22.
//

#ifndef GPU_MONITOR_AMDGPUHANDLER_H
#define GPU_MONITOR_AMDGPUHANDLER_H


#include <amdgpu.h>
#include "../include/GPUHandler.h"

class AMDGPUHandler : public GPUHandler {
private:
    amdgpu_device_handle deviceHandle;
    StaticDeviceData* staticDeviceData;
    MonitoringData* monitoringData;

public:
    CombinedGPUData initializeGPUData(drmDevicePtr devicePtr) override;
    void freeInternals() override;

};


#endif //GPU_MONITOR_AMDGPUHANDLER_H
