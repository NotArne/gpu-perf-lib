//
// Created by arne on 23.03.22.
//
#include <libdrm/amdgpu_drm.h>
#include <libdrm/amdgpu.h>

#include "AMDMonitoringData.h"

AMDMonitoringData::AMDMonitoringData(amdgpu_device_handle handle) : MonitoringData(VENDOR_AMD) {
    this->gpuHandle = handle;
}

int AMDMonitoringData::getTotalGPUWorkload() {
    return 0;
}

void AMDMonitoringData::updateData() {

}