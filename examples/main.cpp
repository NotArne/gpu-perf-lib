#include <iostream>

#include "../gpu-perf-data/include/GPUScanner.h"
#include "../gpu-perf-data/include/ExceptionHandling.h"

int main() {

    GPUScanner scanner;
    std::vector<CombinedGPUData> gpusFound;
    gpusFound = scanner.scanPort();

    std::cout << "GPUs found: " << gpusFound.size() << std::endl;
    std::cout << "Vendor: " << gpusFound[0].getStaticDeviceData()->getVendor() << std::endl;
    std::cout << "Marketing name: " << gpusFound[0].getStaticDeviceData()->getMarketingName()<< std::endl;
    std::cout << "Max ShaderClock:: " << gpusFound[0].getStaticDeviceData()->getMaxShaderClock()<< std::endl;
    std::cout << "Current Memory Clock: " << gpusFound[0].getMonitoringData()->getCurrentMemoryClock()<< std::endl;
    scanner.freeInternalResources();

    return 0;
}
