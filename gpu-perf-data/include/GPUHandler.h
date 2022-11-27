//
// Created by arne on 04.04.22.
//

#ifndef GPU_MONITOR_GPUHANDLER_H
#define GPU_MONITOR_GPUHANDLER_H

#include <vector>
#include <xf86drm.h>
#include "CombinedGPUData.h"

class GPUHandler {

public:
    virtual CombinedGPUData initializeGPUData(drmDevicePtr devicePtr) = 0;
    virtual void freeInternals() = 0;

};


#endif //GPU_MONITOR_GPUHANDLER_H
