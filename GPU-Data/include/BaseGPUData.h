//
// Created by arne on 29.03.22.
//
#include "SupportedVendors.h"

#ifndef GPU_MONITOR_GPUDATA_H
#define GPU_MONITOR_GPUDATA_H

/**
 * Interface representing all information regarding a GPU without differentiate monitoring and static device data
 */
class BaseGPUData {

private:
    const Vendor vendor;
protected:
    BaseGPUData(Vendor vendor);
public:
    virtual void updateData() = 0;
    Vendor getVendor();
};

#endif //GPU_MONITOR_GPUDATA_H
