//
// Created by arne on 04.04.22.
//

#include "AMDGPUHandler.h"
#include "AMDStaticDeviceData.h"
#include "AMDMonitoringData.h"
#include "../include/ExceptionHandling.h"
#include <libdrm/amdgpu.h>
#include <xf86drm.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdint.h>
#include <iostream>
#include <cstring>

CombinedGPUData AMDGPUHandler::initializeGPUData(drmDevicePtr devicePtr) {

    int fd = -1;
    if (devicePtr->available_nodes)
        fd = open(
                devicePtr->nodes[0],
                O_RDWR | O_CLOEXEC);

    drmVersion *version = drmGetVersion(fd);
    if (!version) {

        fprintf(stderr,
                "Warning: Cannot get version for %s."
                "Error is %s\n",
                devicePtr->nodes[0]);
        close(fd);
    }
    if (strcmp(version->name, "amdgpu")) {
        // Not the amdgpu driver!
        drmFreeVersion(version);
        close(fd);
    }
    drmFreeVersion(version);
    std::cout << fd << std::endl;

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
