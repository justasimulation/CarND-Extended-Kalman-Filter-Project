//
// Created by sergey on 29.03.17.
//

#ifndef EXTENDEDKF_MEASUREMENT_DEVICE_H
#define EXTENDEDKF_MEASUREMENT_DEVICE_H

#include <memory>

#include "measurement_package.h"
#include "storage.h"

class MeasurementDevice
{
    private:
        Storage &storage_;

    public:
        MeasurementDevice(Storage &storage);
        MeasurementPackage* GetNextMeasurement();
};

#endif //EXTENDEDKF_MEASUREMENT_DEVICE_H
