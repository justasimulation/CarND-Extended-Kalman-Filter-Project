//
// Created by sergey on 29.03.17.
//

#ifndef EXTENDEDKF_TRACKER_H
#define EXTENDEDKF_TRACKER_H

#include "measurement_package.h"

class Tracker
{
    private:
        unsigned int num_measurements_;
        long unsigned int cumulative_error_;

    public:
        Tracker();
        void ProcessMeasurement(MeasurementPackage &measurement);
};

#endif //EXTENDEDKF_TRACKER_H
