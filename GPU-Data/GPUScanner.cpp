//
// Created by arne on 29.03.22.
//

#include "include/GPUScanner.h"
#include "include/SupportedVendors.h"
#include "include/GPUHandler.h"
#include "amdgpu/AMDGPUHandler.h"

#include <libdrm/amdgpu_drm.h>
#include <libdrm/amdgpu.h>
#include <xf86drm.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdint.h>
#include <iostream>
#include <cstring>

std::vector<CombinedGPUData> GPUScanner::scanPort() {

    std::vector<CombinedGPUData> result;

    drmDevicePtr devices[MAX_PCI_SCAN];
    int fd  = 0;
    int drmCount = drmGetDevices2(0, devices, MAX_PCI_SCAN);
    for(int i = 0; i < drmCount; i++) {
        /* If this is not PCI device, skip*/
        if (devices[i]->bustype != DRM_BUS_PCI) {
            continue; // NO PCI Device -> not a GPU
        }

        // Handle a AMD GPU
        if (devices[i]->deviceinfo.pci->vendor_id == VendorID::VENDOR_ID_AMD) {
            GPUHandler* amdGPUHandler = new AMDGPUHandler;
            CombinedGPUData gpuData = amdGPUHandler->initializeGPUData(devices[i]);
            result.push_back(gpuData);
            internalReferences.push_back(amdGPUHandler);
        }
    }
    return result;
}

void GPUScanner::freeInternalResources() {
    //Free all internal variables
    for(GPUHandler* &handler : internalReferences) {
        handler->freeInternals();
        delete handler;
    }
}