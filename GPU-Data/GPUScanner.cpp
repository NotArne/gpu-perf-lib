//
// Created by arne on 29.03.22.
//

#include "include/GPUScanner.h"
#include "include/SupportedVendors.h"

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

            fd = -1;
            if (devices[i]->available_nodes)
                fd = open(
                        devices[i]->nodes[i],
                        O_RDWR | O_CLOEXEC);

            drmVersion *version = drmGetVersion(fd);
            if (!version) {

                fprintf(stderr,
                        "Warning: Cannot get version for %s."
                        "Error is %s\n",
                        devices[i]->nodes[i]);
                close(fd);
            }
            if (strcmp(version->name, "amdgpu")) {
                /* This is not AMDGPU driver, skip.*/
                drmFreeVersion(version);
                close(fd);
            }
            drmFreeVersion(version);
            /*drm_amdgpu[amd_index] = fd;
            amd_index++; */
            std::cout << fd << std::endl;

            amdgpu_device_handle device_handle;
            uint32_t major_version, minor_version;

            int res = amdgpu_device_initialize(fd, &major_version, &minor_version, &device_handle);

            if(res == 0) {
                CombinedGPUData data;
            }
        }
    }
    return result;
}

void GPUScanner::deconstructInternalResources() {

}