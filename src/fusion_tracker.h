#ifndef EXTENDEDKF_FUSION_TRACKER_H
#define EXTENDEDKF_FUSION_TRACKER_H

#include "Eigen/Dense"
#include "measurement_package.h"
#include "kalman_filter_state.h"
#include "laser_filter.h"
#include "radar_filter.h"
#include "fusion_tracker_result.h"

/**
 * Represents fusion tracker. Uses dedicated filters for radar and laser measurements to track an object.
 * Laser filter is a Kalamn filter, rader filter is an extended Kalman filter.
 * This class contains common KalmanFilterState that is updated by both filters.
 */
class FusionTracker
{
    private:
        //number of measurements processed so far
        unsigned int num_measurements_;

        //accumulates square error so RMSE could be calculated
        Eigen::VectorXd cumulative_square_error_;

        //when first measurement is read, it should be used to iniialize the state,
        //after that this flag should be put to true
        bool is_initialized_;

        //this one is used to calculate deltat time, which is used in state transition and process covariance
        //matrices
        long previous_timestamp_;

        //filter state shared by all the filters
        KalmanFilterState common_filter_state_;

        LaserFilter laser_filter_;
        RadarFilter radar_filter_;

    public:
        /**
         * Constructor. Initializes values, filters, couples filters with the state.
         */
        FusionTracker();

        /**
         * On first call initializes shared filter state with given measurement.
         * On next calls performs predict, update steps on filters chosen by measurement type.
         * @param measurement
         * @param result
         */
        void ProcessMeasurement(MeasurementPackage &measurement, FusionTrackerResult &result);

        /**
         * Calculates RMSE for data processed so far.
         * @return Vector(4) of rmse for x, y, vx, vy
         */
        Eigen::VectorXd GetRMSE();


    private:
        /**
         * Calculates square error between given ground truth and current state.
         * Adds this error to the existing value.
         * @param ground_truth
         */
        void AddSquareError(const Eigen::VectorXd &ground_truth);

        /**
         * Returns eigher radar or laser filter based on measurement type.
         * In case measurment type is uknown the program is stopped.
         * @param measurement - measurement package
         * @return eigher radar_filer_ or laser_filer_
         */
        SensorFilterBase& ChooseFilter(const MeasurementPackage &measurement);

        /**
         * Initializes shared filter state with given cartesian state vector, which should be retrived from
         * the first measurement. Also covariance state matrix is initialized with fixed values.
         * @param cartesian_x - Vector=(x, y, vx, vy)
         */
        void InitializeState(const Eigen::VectorXd &cartesian_x);
};

#endif //EXTENDEDKF_FUSION_TRACKER_H
