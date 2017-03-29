#include "tracker.h"

Tracker::Tracker()
{
}

void Tracker::ProcessMeasurement(MeasurementPackage &measurement)
{
    num_measurements_++;
    cumulative_error_+=10;
}
