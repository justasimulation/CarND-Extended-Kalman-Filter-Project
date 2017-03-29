#ifndef EXTENDEDKF_FUSION_TRACKER_H
#define EXTENDEDKF_FUSION_TRACKER_H

#include "measurement_package.h"

class FusionTracker
{
    private:
        unsigned int num_measurements_;
        long unsigned int cumulative_error_;

    public:
        FusionTracker();
        void OnMeasurementRecieved(MeasurementPackage &measurement);
};

#endif //EXTENDEDKF_FUSION_TRACKER_H
