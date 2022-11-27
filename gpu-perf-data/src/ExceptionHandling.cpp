//
// Created by arne on 06.04.22.
//

#include "../include/ExceptionHandling.h"

GPUInitializationFailureException::GPUInitializationFailureException(Vendor vendor, int errorCode) : vendor(vendor), errorCode(errorCode) {}

const char *GPUInitializationFailureException::what() const noexcept {
    return "Failed to initialize GPU!";
}

Vendor GPUInitializationFailureException::getVendor() {
    return vendor;
}

int GPUInitializationFailureException::getErrorCode() {
    return errorCode;
}


GPUDataRetrievingFailureException::GPUDataRetrievingFailureException(std::string errorMessage, Vendor vendor,
                                                                     int errorCode) : errorMessage(errorMessage),vendor(vendor), errorCode(errorCode){}

const char *GPUDataRetrievingFailureException::what() const noexcept {
    return errorMessage.c_str();
}

Vendor GPUDataRetrievingFailureException::getVendor() {
    return vendor;
}

int GPUDataRetrievingFailureException::getErrorCode() {
    return errorCode;
}


GPUDataRetrievingUnsupportedException::GPUDataRetrievingUnsupportedException(std::string errorMessage, std::string queryParameter, Vendor vendor)
: errorMessage(errorMessage), queryParameter(queryParameter), vendor(vendor) {}

const char *GPUDataRetrievingUnsupportedException::what() const noexcept {
    return errorMessage.c_str();
}

Vendor GPUDataRetrievingUnsupportedException::getVendor() {
    return vendor;
}

std::string GPUDataRetrievingUnsupportedException::getQueryParameter() {
    return queryParameter;
}