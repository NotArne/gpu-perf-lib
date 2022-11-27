//
// Created by arne on 30.03.22.
//

#include "../include/BaseGPUData.h"

BaseGPUData::BaseGPUData(Vendor vendor) : vendor(vendor){ }

Vendor BaseGPUData::getVendor() {
    return vendor;
}
