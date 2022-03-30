//
// Created by arne on 23.03.22.
//
#include "BaseGPUData.h"

#ifndef GPU_MONITOR_DEVICEDATA_H
#define GPU_MONITOR_DEVICEDATA_H

/**
 * Interface representing all static information regarding a GPU
 */
class StaticDeviceData : BaseGPUData {

public:

    virtual int getMaxShaderClock() = 0;
    virtual int getMaxMemoryClock() = 0;
    virtual int getTotalVRAM() = 0;

};

#endif //GPU_MONITOR_DEVICEDATA_H
