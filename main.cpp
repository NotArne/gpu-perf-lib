#include <iostream>

#include <libdrm/amdgpu_drm.h>
#include <libdrm/amdgpu.h>
#include <xf86drm.h>

#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdint.h>
#include "GPU-Data/amdgpu/AMDMonitoringData.h"

int main() {
    std::cout << "Hello, World!" << std::endl;

    drmDevicePtr devices[2];
    int fd  = 0;
    int drm_count = drmGetDevices2(0, devices, 2);
        /* If this is not PCI device, skip*/
        if (devices[0]->bustype != DRM_BUS_PCI)
            std::cerr << "No PCI Device" << std::endl;
        /* If this is not AMD GPU vender ID, skip*/
        if (devices[0]->deviceinfo.pci->vendor_id != 0x1002)
            std::cerr << "Not AMD GPU" << std::endl;
        fd = -1;
        if (devices[0]->available_nodes)
            fd = open(
                    devices[0]->nodes[0],
                    O_RDWR | O_CLOEXEC);

        drmVersion* version = drmGetVersion(fd);
        if (!version) {

            fprintf(stderr,
                    "Warning: Cannot get version for %s."
                    "Error is %s\n",
                    devices[0]->nodes[0]);
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
    std::cout << drm_count << std::endl;

    amdgpu_device_handle device_handle;
    uint32_t major_version, minor_version;

    int res = amdgpu_device_initialize(fd, &major_version, &minor_version, &device_handle);
    std::cout << "Res: " << res << std::endl;

    struct amdgpu_gpu_info gpu;
    amdgpu_query_gpu_info(device_handle, &gpu);

    std::cout << gpu.num_shader_engines << std::endl;

    unsigned int* temp = new unsigned int[1];
    drm_amdgpu_info info;
    int resSensor = amdgpu_query_sensor_info(device_handle, AMDGPU_INFO_SENSOR_GPU_TEMP, sizeof(info), &info);
    std::cout << amdgpu_get_marketing_name(device_handle) << std::endl;
    AMDMonitoringData data(device_handle);
    return 0;
}
