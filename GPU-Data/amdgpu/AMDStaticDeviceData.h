//
// Created by arne on 29.03.22.
//

#ifndef GPU_MONITOR_AMDSTATICDEVICEDATA_H
#define GPU_MONITOR_AMDSTATICDEVICEDATA_H


#include <amdgpu.h>
#include "../include/StaticDeviceData.h"

class AMDStaticDeviceData : public StaticDeviceData {
private:
    amdgpu_device_handle gpuHandle;

    // Member value variables
    std::string marketingName;
    int maxShaderClock;
    int maxMemoryClock;
    long totalVRAM;
    int memoryBitWidth;
    int amountOfCUs;
    int amountOfShaders;


public:
    explicit AMDStaticDeviceData(amdgpu_device_handle gpuHandle);

    std::string getMarketingName() override;

    void updateData() override;

    int getMaxShaderClock() override;

    int getMaxMemoryClock() override;

    long getTotalVRAM() override;

    int getMaxMemoryBitWidth() override;

    int getAmountOfShaders() override;

    int getAmountOfComputeUnits() override;
};


#endif //GPU_MONITOR_AMDSTATICDEVICEDATA_H
