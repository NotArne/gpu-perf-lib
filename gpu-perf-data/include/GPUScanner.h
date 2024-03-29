//
// Created by arne on 29.03.22.
//

#ifndef GPU_MONITOR_GPUSCANNER_H
#define GPU_MONITOR_GPUSCANNER_H

#include "CombinedGPUData.h"
#include "GPUHandler.h"
#include <vector>

/**
 * Scans the PCI interface and extracts supported GPUs
 */
class GPUScanner {
private:
    const int MAX_PCI_SCAN = 20;
    std::vector<GPUHandler*> internalReferences;

public:
    std::vector<CombinedGPUData> scanPort();
    void freeInternalResources();
};


#endif //GPU_MONITOR_GPUSCANNER_H
