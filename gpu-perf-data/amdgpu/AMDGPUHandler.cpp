//
// Created by arne on 04.04.22.
//

#include "include/AMDGPUHandler.h"
#include "include/AMDStaticDeviceData.h"
#include "include/AMDMonitoringData.h"
#include "../include/ExceptionHandling.h"
#include <libdrm/amdgpu.h>
#include <xf86drm.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdint.h>
#include <cstring>

CombinedGPUData AMDGPUHandler::initializeGPUData(drmDevicePtr devicePtr) {

    int fd = -1;
    if (devicePtr->available_nodes)
        fd = open(
                devicePtr->nodes[0],
                O_RDWR | O_CLOEXEC);

    drmVersion *version = drmGetVersion(fd);
    if (!version) {
        throw GPUInitializationFailureException(VENDOR_AMD_AMDGPU, 1);
        close(fd);
    }
    if (strcmp(version->name, "amdgpu")) {
        // Not the amdgpu driver!
        drmFreeVersion(version);
        close(fd);
        throw GPUInitializationFailureException(VENDOR_AMD_AMDGPU, 2);
    }
    drmFreeVersion(version);

    uint32_t majorVersion, minorVersion;

    int res = amdgpu_device_initialize(fd, &majorVersion, &minorVersion, &deviceHandle);

    if(res == 0) {
        staticDeviceData = new AMDStaticDeviceData(deviceHandle);
        monitoringData = new AMDMonitoringData(deviceHandle);
        CombinedGPUData data(staticDeviceData, monitoringData);
        return data;
    } else {
        throw GPUInitializationFailureException(VENDOR_AMD_AMDGPU, res); // Exception
    }
}

void AMDGPUHandler::freeInternals() {
    amdgpu_device_deinitialize(deviceHandle);
    delete staticDeviceData;
    delete monitoringData;
}
