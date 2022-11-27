//
// Created by arne on 29.03.22.
//

#ifndef GPU_MONITOR_AMDSTATICDEVICEDATA_H
#define GPU_MONITOR_AMDSTATICDEVICEDATA_H


#include <amdgpu.h>
#include "../../include/StaticDeviceData.h"

class AMDStaticDeviceData : public StaticDeviceData {
private:
    amdgpu_device_handle gpuHandle;

    // Member value variables
    std::string marketingName;
    uint64_t maxShaderClock;
    uint64_t maxMemoryClock;
    uint64_t totalVRAM;
    uint32_t memoryBitWidth;
    uint32_t amountOfCUs;
    uint32_t amountOfShaders;


public:
    explicit AMDStaticDeviceData(amdgpu_device_handle gpuHandle);

    std::string getMarketingName() override;

    void updateData() override;

    uint64_t getMaxShaderClock() override;

    uint64_t getMaxMemoryClock() override;

    uint64_t getTotalVRAM() override;

    uint32_t getMemoryBitWidth() override;

    uint32_t getAmountOfShaders() override;

    uint32_t getAmountOfComputeUnits() override;

};


#endif //GPU_MONITOR_AMDSTATICDEVICEDATA_H
