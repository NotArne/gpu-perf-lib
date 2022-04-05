#include <iostream>

#include "GPU-Data/include/GPUScanner.h"

int main() {

    GPUScanner scanner;
    std::vector<CombinedGPUData> gpusFound = scanner.scanPort();
    std::cout << "GPUs found: " << gpusFound.size() << std::endl;
    std::cout << "Vendor: " << gpusFound[0].getStaticDeviceData()->getVendor() << std::endl;
    std::cout << "Marketing name: " << gpusFound[0].getStaticDeviceData()->getMarketingName() << std::endl;
    std::cout << "Total VRAM: " << gpusFound[0].getStaticDeviceData()->getTotalVRAM() << std::endl;
    std::cout << "Total Amount of Shaders: " << gpusFound[0].getStaticDeviceData()->getMaxMemoryClock() << std::endl;
    scanner.freeInternalResources();

    return 0;
}
