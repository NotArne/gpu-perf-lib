//
// Created by arne on 30.03.22.
//

#ifndef GPU_MONITOR_SUPPORTEDVENDORS_H
#define GPU_MONITOR_SUPPORTEDVENDORS_H

enum Vendor : int { VENDOR_AMD_AMDGPU, VENDOR_INTEL, VENDOR_NVIDIA_NOUVEAU, VENDOR_NVIDIA_CS};

struct VendorID {
    static const int VENDOR_ID_AMD = 0x1002;
    static const int VENDOR_ID_NVIDIA = 0x10DE;
    static const int VENDOR_ID_INTEL = 0x8086;
};

#endif //GPU_MONITOR_SUPPORTEDVENDORS_H
