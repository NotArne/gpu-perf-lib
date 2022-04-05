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
    virtual int getTotalGPUWorkload() = 0;

    virtual long getUsedVRAM() = 0;

    virtual int getCurrentMemoryClock() = 0;

    virtual int getCurrentShaderClock() = 0;

    /**
     *
     * @return Temperature of the Chip in °Celsius
     */
    virtual int getChipTemperature() = 0;

    virtual int getCurrentPowerConsumption() = 0;

};


#endif //GPU_MONITOR_MONITORINGDATA_H
