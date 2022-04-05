//
// Created by arne on 23.03.22.
//
#include <string>
#include "BaseGPUData.h"

#ifndef GPU_MONITOR_DEVICEDATA_H
#define GPU_MONITOR_DEVICEDATA_H

/**
 * Interface representing all static information regarding a GPU
 */
class StaticDeviceData : public BaseGPUData {
protected:
    explicit StaticDeviceData(Vendor vendor) : BaseGPUData(vendor) {};

public:
    virtual std::string getMarketingName() = 0;
    virtual int getMaxShaderClock() = 0;
    virtual int getAmountOfShaders() = 0;
    virtual int getAmountOfComputeUnits() = 0;
    virtual int getMaxMemoryClock() = 0;
    virtual int getMaxMemoryBitWidth() = 0;
    virtual long getTotalVRAM() = 0;

};

#endif //GPU_MONITOR_DEVICEDATA_H
