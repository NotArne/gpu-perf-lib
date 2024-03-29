//
// Created by arne on 29.03.22.
//

#include <xf86drm.h>
#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>

#include "../include/GPUScanner.h"
#include "../include/GPUHandler.h"

#ifdef AMDGPU_FOUND
#include "../amdgpu/include/AMDGPUHandler.h"
#endif

#ifdef NVIDIA_FOUND
#include "../nvidia/include/NvidiaHandler.h"
#endif

std::vector<CombinedGPUData> GPUScanner::scanPort() {

    std::vector<CombinedGPUData> result;

    drmDevicePtr devices[MAX_PCI_SCAN];
    int fd  = 0;
    int drmCount = drmGetDevices2(0, devices, MAX_PCI_SCAN);
    for(int i = 0; i < drmCount; i++) {
        /* If this is not PCI device, skip*/
        if (devices[i]->bustype != DRM_BUS_PCI) {
            continue; // Not a PCI Device -> not a GPU
        }
#ifdef AMDGPU_FOUND
        // Handle a AMD GPU
        if (devices[i]->deviceinfo.pci->vendor_id == VendorID::VENDOR_ID_AMD) {
            GPUHandler* amdGPUHandler = new AMDGPUHandler;
            CombinedGPUData gpuData = amdGPUHandler->initializeGPUData(devices[i]);
            result.push_back(gpuData);
            internalReferences.push_back(amdGPUHandler);
        }
#endif

#ifdef NVIDIA_FOUND
        //Handle a NVIDIA GPU
        if(devices[i]->deviceinfo.pci->vendor_id == VendorID::VENDOR_ID_NVIDIA) {
            GPUHandler* nvidiaGPUHandler = new NvidiaHandler;
            CombinedGPUData gpuData = nvidiaGPUHandler->initializeGPUData(devices[i]);
            result.push_back(gpuData);
            internalReferences.push_back(nvidiaGPUHandler);
        }
#endif

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