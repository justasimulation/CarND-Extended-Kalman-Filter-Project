#include "measurement_device.h"

MeasurementDevice::MeasurementDevice(Storage &storage) :storage_(storage) {}

MeasurementPackage* MeasurementDevice::GetNextMeasurement()
{
    return storage_.GetNextMeasurement();
}

