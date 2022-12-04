# gpu-monitor

## Status:
Actually, this is a pre-alpha version. Linking will be very soon generalized using linking at runtime in order to detect the right existent libraries on system at runtime.

## Motivation:
A simple library which aims to generalize the access to GPU performance data on Linux systems for AMD (amdgpu driver) and NVIDIA GPUs. Intel will be perhaps implemented later, if Intel provides information via a library or its kernel driver.

## Build:
You can build a test version via the CMake file. Check permissions on launching the program. Change the libnvidia-ml.so path so that it matches to your systems one.
