//
// Created by arne on 09.04.22.
//

#ifndef GPU_MONITOR_NVIDIAHELPER_H
#define GPU_MONITOR_NVIDIAHELPER_H

#include <nvml.h>
#include <string>

class NvidiaHelper {

public:
    static void throwConcreteError(nvmlReturn_enum queryResult, std::string queryData);
};

#endif //GPU_MONITOR_NVIDIAHELPER_H
