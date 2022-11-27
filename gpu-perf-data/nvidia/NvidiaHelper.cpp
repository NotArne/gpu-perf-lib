//
// Created by arne on 09.04.22.
//

#include "include/NvidiaHelper.h"
#include "../include/ExceptionHandling.h"

void NvidiaHelper::throwConcreteError(nvmlReturn_enum queryResult, std::string queryData) {
    if(queryResult == NVML_SUCCESS) {
        return;
    }

    if(queryResult == NVML_ERROR_NOT_SUPPORTED) {
        throw GPUDataRetrievingUnsupportedException("Retrieving this data from the GPU is unsupported!", queryData, VENDOR_NVIDIA_CS);
    } else {
        throw GPUDataRetrievingFailureException("Failed to retrieve Data", VENDOR_NVIDIA_CS, queryResult);
    }
}