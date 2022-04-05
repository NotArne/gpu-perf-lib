//
// Created by arne on 30.03.22.
//

#ifndef GPU_MONITOR_COMBINEDGPUDATA_H
#define GPU_MONITOR_COMBINEDGPUDATA_H


#include "StaticDeviceData.h"
#include "MonitoringData.h"

class CombinedGPUData {

private:
    StaticDeviceData* staticDeviceData;
    MonitoringData* monitoringData;

public:
    CombinedGPUData(StaticDeviceData* staticDeviceData, MonitoringData* monitoringData);
    ~CombinedGPUData() = default;

    StaticDeviceData *getStaticDeviceData() const;

    void setStaticDeviceData(StaticDeviceData *staticDeviceData);

    MonitoringData *getMonitoringData() const;

    void setMonitoringData(MonitoringData *monitoringData);
};


#endif //GPU_MONITOR_COMBINEDGPUDATA_H
