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
    virtual void updateData() = 0;
    virtual std::string getMarketingName() = 0;
    virtual uint64_t getMaxShaderClock() = 0;
    virtual uint32_t getAmountOfShaders() = 0;
    virtual uint32_t getAmountOfComputeUnits() = 0;
    virtual uint64_t getMaxMemoryClock() = 0;
    virtual uint32_t getMemoryBitWidth() = 0;
    virtual uint64_t getTotalVRAM() = 0;

};

#endif //GPU_MONITOR_DEVICEDATA_H
