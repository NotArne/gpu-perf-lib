//
// Created by arne on 05.04.22.
//

#ifndef GPU_MONITOR_EXCEPTIONHANDLING_H
#define GPU_MONITOR_EXCEPTIONHANDLING_H

#include <exception>
#include <string>
#include "SupportedVendors.h"

/**
 * Exception which will be thrown if initialization of GPU fails. If this happens, it is not necessary to read data from it later!
 */
class GPUInitializationFailureException : public std::exception {
    Vendor vendor;
    int errorCode;
public:
    explicit GPUInitializationFailureException(Vendor vendor, int errorCode);

    const char* what() const noexcept override;

    Vendor getVendor();

    int getErrorCode();
};

class GPUDataRetrievingFailureException : public std::exception {
    Vendor vendor;
    int errorCode;
    std::string errorMessage;
public:
    explicit GPUDataRetrievingFailureException(std::string errorMessage, Vendor vendor, int errorCode);

    const char* what() const noexcept override;

    Vendor getVendor();

    int getErrorCode();
};

class GPUDataRetrievingUnsupportedException : public std::exception {
    Vendor vendor;
    std::string errorMessage;
    std::string queryParameter;

    std::string returnMessage;
public:
    explicit GPUDataRetrievingUnsupportedException(std::string errorMessage, std::string queryParameter, Vendor vendor);

    const char* what() const noexcept override;

    Vendor getVendor();

    std::string getQueryParameter();
};


#endif //GPU_MONITOR_EXCEPTIONHANDLING_H
