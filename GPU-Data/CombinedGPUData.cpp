//
// Created by arne on 30.03.22.
//

#include "include/CombinedGPUData.h"

CombinedGPUData::CombinedGPUData(StaticDeviceData* staticDeviceData, MonitoringData* monitoringData) {
    this->staticDeviceData = staticDeviceData;
    this->monitoringData = monitoringData;
}

StaticDeviceData *CombinedGPUData::getStaticDeviceData() const {
    return staticDeviceData;
}

void CombinedGPUData::setStaticDeviceData(StaticDeviceData *staticDeviceData) {
    CombinedGPUData::staticDeviceData = staticDeviceData;
}

MonitoringData *CombinedGPUData::getMonitoringData() const {
    return monitoringData;
}

void CombinedGPUData::setMonitoringData(MonitoringData *monitoringData) {
    CombinedGPUData::monitoringData = monitoringData;
}
