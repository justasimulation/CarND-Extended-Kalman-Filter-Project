#include "fusion_tracker.h"

FusionTracker::FusionTracker()
{
}

void FusionTracker::OnMeasurementRecieved(MeasurementPackage &measurement)
{
    num_measurements_++;
    cumulative_error_+=10;
}
