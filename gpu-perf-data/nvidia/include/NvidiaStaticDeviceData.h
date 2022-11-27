//
// Created by arne on 09.04.22.
//

#ifndef GPU_MONITOR_NVIDIASTATICDEVICEDATA_H
#define GPU_MONITOR_NVIDIASTATICDEVICEDATA_H

#include <nvml.h>
#include "../../include/StaticDeviceData.h"

class NvidiaStaticDeviceData : public StaticDeviceData {

private:
    nvmlDevice_t gpuHandle;

    std::string marketingName;
    nvmlReturn_enum hasMarketingName;

    uint64_t maxShaderClock;
    nvmlReturn_enum hasMaxShaderClock;

    uint64_t maxMemoryClock;
    nvmlReturn_enum hasMaxMemoryClock;

    uint64_t totalVRAM;
    nvmlReturn_enum hasTotalVRAM;

    uint32_t memoryBitWidth;
    nvmlReturn_enum hasMemoryBitWidth;

    uint32_t amountOfCUs;
    nvmlReturn_enum hasAmountOfCUs;

    uint32_t amountOfShaders;
    nvmlReturn_enum hasAmountOfShaders;

public:
    explicit NvidiaStaticDeviceData(nvmlDevice_t gpuHandle);

    std::string getMarketingName() override;

    void updateData() override;

    uint64_t getMaxShaderClock() override;

    uint64_t getMaxMemoryClock() override;

    uint64_t getTotalVRAM() override;

    uint32_t getMemoryBitWidth() override;

    uint32_t getAmountOfShaders() override;

    uint32_t getAmountOfComputeUnits() override;

};

#endif //GPU_MONITOR_NVIDIASTATICDEVICEDATA_H
