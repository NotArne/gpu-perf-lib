//
// Created by arne on 08.04.22.
//

#ifndef GPU_MONITOR_NVIDIAHANDLER_H
#define GPU_MONITOR_NVIDIAHANDLER_H


#include <nvml.h>
#include "../../include/GPUHandler.h"

/**
 * Handles the initialization of the NVDL library to access GPU performance data
 */
class NvidiaHandler : public GPUHandler {
private:
    nvmlDevice_t deviceData;
    StaticDeviceData* staticDeviceData;
    MonitoringData* monitoringData;

public:
    CombinedGPUData initializeGPUData(drmDevicePtr devicePtr) override;

    void freeInternals() override;
};

#endif //GPU_MONITOR_NVIDIAHANDLER_H
