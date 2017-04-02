#ifndef EXTENDEDKF_SENSOR_FILTER_BASE_H
#define EXTENDEDKF_SENSOR_FILTER_BASE_H

#include "Eigen/Dense"

#include "kalman_filter.h"

/**
 * Represents more concrete extension of KalmanFilter that contains common code for particular
 * laser and radar filters.
 */
class SensorFilterBase : public KalmanFilter
{
    private:
        //variable matrix that is used to calculate process covariance matrix Q_
        Eigen::MatrixXd G_;
        
        //constant matrix that is used to calculate process covariance matrix Q_
        Eigen::MatrixXd Qv_;

    public:
        /**
         * Constructor. Initializes matrices with particular numbers or sizes and
         * memorizes given state.
         * @param state - common filter state
         */
        SensorFilterBase(KalmanFilterState &state);
    
        /**
         * Updates state transition matrix F_ and process covariance matrix Q_ with given
         * time delta
         * @param delta_time - time passed from the last update in seconds
         */
        void SetDeltaTime(float delta_time);
    
        /**
         * Returns cartesian state vector from given measurement vector.
         * @param raw_measurement - measurement vector as it was read from the measurement source
         * @param x - reference to the result vector which values should be set. No need for reinstantiation.
         */
        void virtual GetCartesianStateVector(const Eigen::VectorXd &raw_measurement, Eigen::VectorXd &x) = 0;
};

#endif //EXTENDEDKF_SENSOR_FILTER_BASE_H
