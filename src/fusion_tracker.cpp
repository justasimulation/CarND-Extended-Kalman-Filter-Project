#include <iostream>

#include "fusion_tracker.h"

using namespace Eigen;

/**
 * Constructor. Initializes values, filters, couples filters with the state.
 */
FusionTracker::FusionTracker() : laser_filter_(common_filter_state_), radar_filter_(common_filter_state_)
{
    is_initialized_ = false;
    previous_timestamp_ = 0;
    num_measurements_ = 0;

    cumulative_square_error_ = VectorXd(4);
    cumulative_square_error_ << 0, 0, 0, 0;
}

/**
 * On first call initializes shared filter state with given measurement.
 * On next calls performs predict, update steps on filters chosen by measurement type.
 * @param measurement
 * @param result
 */
void FusionTracker::ProcessMeasurement(MeasurementPackage &measurement, FusionTrackerResult &result)
{
    //increment number of measurements,
    //we count every measurement even if update cannot be calculated
    num_measurements_++;

    //choose radar or laser filter
    SensorFilterBase &filter = ChooseFilter(measurement);

    //get cartisian representation of the measuement
    VectorXd cartesian_x = VectorXd(4);
    filter.GetCartesianStateVector(measurement.raw_measurements_, cartesian_x);

    //in case this is the first call, initialize the state with the first measurment and a fixed covariance matrix
    if(!is_initialized_)
    {
        previous_timestamp_ = measurement.timestamp_;
        InitializeState(cartesian_x);

        is_initialized_ = true;
    }
    else
    {
        //calculate time delta
        float dt = (measurement.timestamp_ - previous_timestamp_) / 1000000.0;

        //check that time in ascending order
        if(dt < 0)
        {
            std::cerr << "Incorrect time order. Delta time: " << dt << std::endl;
            exit(EXIT_FAILURE);
        }

        //memorize current time to calculate time delta next time
        previous_timestamp_ = measurement.timestamp_;

        //pass time delta to filter so it can calculate F_ and Q_ matrices
        filter.SetDeltaTime(dt);

        //perform predict step
        filter.Predict();

        //perform update step
        filter.Update(measurement.raw_measurements_);
    }

    //accumulate error
    AddSquareError(measurement.ground_truth_);

    //return estimation and cartesian measurement
    result = FusionTrackerResult();
    result.estimation_ = common_filter_state_.x_;
    result.measurement_ = cartesian_x;
}

/**
 * Initializes shared filter state with given cartesian state vector, which should be retrived from
 * the first measurement. Also covariance state matrix is initialized with fixed values.
 * @param cartesian_x - Vector=(x, y, vx, vy)
 */
void FusionTracker::InitializeState(const VectorXd &cartesian_x)
{
    // 1 and 1000 are some magic numbers,
    // they reflect the fact that we are kind of confident in x and y because we take them
    // from the 1st measurement, but we may know nothing about speed
    common_filter_state_.P_ = MatrixXd(4, 4);
    common_filter_state_.P_ <<  1, 0, 0,    0,
                                0, 1, 0,    0,
                                0, 0, 1000, 0,
                                0, 0, 0,    1000;

    common_filter_state_.x_ = cartesian_x;
}

/**
 * Returns eigher radar or laser filter based on measurement type.
 * In case measurment type is uknown the program is stopped.
 * @param measurement - measurement package
 * @return eigher radar_filer_ or laser_filer_
 */
SensorFilterBase& FusionTracker::ChooseFilter(const MeasurementPackage &measurement)
{
    switch(measurement.sensor_type_)
    {
        case MeasurementPackage::LASER:
        {
            return laser_filter_;
        }
        case MeasurementPackage::RADAR:
        {
            return radar_filter_;
        }
        default:
        {
            std::cerr << "Incorrect sensor type: " << measurement.sensor_type_ << std::endl;
            exit(EXIT_FAILURE);
        }
    }
}

/**
 * Calculates square error between given ground truth and current state.
 * Adds this error to the existing value.
 * @param ground_truth
 */
void FusionTracker::AddSquareError(const VectorXd &ground_truth)
{
    VectorXd square_error = (common_filter_state_.x_ - ground_truth).array().pow(2);
    cumulative_square_error_ += square_error;
}

VectorXd FusionTracker::GetRMSE()
{
    return (cumulative_square_error_ / num_measurements_).array().sqrt();
}
