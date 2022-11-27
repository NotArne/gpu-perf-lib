//
// Created by arne on 08.04.22.
//

#include <iostream>
#include "include/NvidiaHandler.h"
#include "../include/ExceptionHandling.h"
#include "include/NvidiaStaticDeviceData.h"
#include "include/NvidiaMonitoringData.h"

CombinedGPUData NvidiaHandler::initializeGPUData(drmDevicePtr devicePtr) {
    nvmlInit_v2();
    //Build combined id string
    std::string deviceBusID;
    deviceBusID += std::to_string(devicePtr->businfo.pci->bus) + ":" + std::to_string(devicePtr->businfo.pci->dev) + "." + std::to_string(devicePtr->businfo.pci->func);

    std::cout << "Device Bus ID: "  << deviceBusID  <<std::endl;
    nvmlReturn_t res = nvmlDeviceGetHandleByPciBusId_v2(deviceBusID.c_str(), &deviceData);
    if(res != NVML_SUCCESS) {
        throw GPUInitializationFailureException(VENDOR_NVIDIA_CS, res);
    }

    staticDeviceData = new NvidiaStaticDeviceData(deviceData);
    monitoringData = new NvidiaMonitoringData(deviceData);
    return CombinedGPUData(staticDeviceData, monitoringData);
}

void NvidiaHandler::freeInternals() {
    nvmlShutdown();
    delete staticDeviceData;
    delete monitoringData;
}
