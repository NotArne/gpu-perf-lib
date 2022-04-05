//
// Created by arne on 23.03.22.
//
#include "BaseGPUData.h"

#ifndef GPU_MONITOR_MONITORINGDATA_H
#define GPU_MONITOR_MONITORINGDATA_H

/**
 * Interface representing all data concerning the actual GPU load
 */
class MonitoringData : public BaseGPUData {

protected:
    explicit MonitoringData(Vendor vendor) : BaseGPUData(vendor) {};

public:
    /**
     * @return Total GPU workload in percent
     */
    virtual uint32_t getTotalGPUWorkload() = 0;

    virtual uint64_t getUsedVRAM() = 0;

    virtual uint32_t getCurrentMemoryClock() = 0;

    virtual uint32_t getCurrentShaderClock() = 0;

    /**
     *
     * @return Temperature of the Chip in milli degrees celsius
     */
    virtual uint32_t getChipTemperature() = 0;

    /**
    *
    * @return Temperature of the Chip in milli watts
    */
    virtual uint32_t getCurrentPowerConsumption() = 0;

};


#endif //GPU_MONITOR_MONITORINGDATA_H
