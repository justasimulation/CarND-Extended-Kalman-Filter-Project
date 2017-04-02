#include "Eigen/Dense"
#include "sensor_filter_base.h"

using namespace Eigen;

/**
 * Constructor. Initializes matrices with particular numbers or sizes and
 * memorizes given state.
 * @param state - common filter state
 */
SensorFilterBase::SensorFilterBase(KalmanFilterState &state) : KalmanFilter(state)
{
    //The following matrices are initialized, but will be changed later
    F_ = MatrixXd(4, 4);
    F_ <<   1, 0, 1, 0,
            0, 1, 0, 1,
            0, 0, 1, 0,
            0, 0, 0, 1;

    Q_ = MatrixXd(4, 4);
    Q_ <<   0, 0, 0, 0,
            0, 0, 0, 0,
            0, 0, 0, 0,
            0, 0, 0, 0;

    G_ = MatrixXd(4, 2);
    G_ <<   0, 0,
            0, 0,
            0, 0,
            0, 0;

    R_ = MatrixXd(2, 2);
    R_ <<   0, 0,
            0, 0;

    //The following matrices will not be changed, they are constant

    Qv_ = MatrixXd(2, 2);
    Qv_ <<  9, 0,
            0, 9;

    long size = F_.rows();
    I_ = MatrixXd::Identity(size, size);
}

/**
 * Updates state transition matrix F_ and process covariance matrix Q_ with given
 * time delta
 * F_ = 1, 0, dt, 0
 *      0, 1, 0, dt,
 *      0, 0, 1, 0,
 *      0, 0, 0, 1
 *
 * Q_ = G * Qv * G.trnapose()
 *
 * G_ = dt**2 / 2, 0,
 *     0,         dt**2/2,
 *     dt,        0,
 *     0,         dt
 *
 * Qv_ = 9, 0
 *       0, 9
 * @param delta_time - time passed from the last update in seconds
 */
void SensorFilterBase::SetDeltaTime(float delta_time)
{
    F_(0, 2) = delta_time;
    F_(1, 3) = delta_time;

    float delta_time_2 = delta_time * delta_time / 2;
    G_(0, 0) = delta_time_2;
    G_(1, 1) = delta_time_2;
    G_(2, 0) = delta_time;
    G_(3, 1) = delta_time;

    Q_ = G_ * Qv_ * G_.transpose();
}
