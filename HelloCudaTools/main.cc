#include <cstdlib>

// CudaTools
#include <GpuDevice.h>


int main(int, char *[]) {

  ct::GpuDevice *device = ct::GpuDevice::GetInstance();
  device->SetDevices();
  device->PrintUsage();

  return EXIT_SUCCESS;
}
