#include <iostream>

#include "kalman_filter.h"

using namespace Eigen;

/**
 * Copnstructor. Memorizes state.
 * @param state
 */
KalmanFilter::KalmanFilter(KalmanFilterState &state):state_(state)
{
}

/**
 * Performs prediction step of the filter.
 */
void KalmanFilter::Predict()
{
    state_.x_ = F_ * state_.x_;
    state_.P_ = (F_ * state_.P_ * F_.transpose()) + Q_;
}

/**
 * Performs update step of the filter.
 * @param z - measurement vector
 */
void KalmanFilter::Update(const VectorXd &z)
{
    VectorXd h = (H_ * state_.x_);
    Update(z, h);
}

/**
 * Performs update step of the filter.
 * Allows to implement extended Kalman filter.
 * In case h = H_ * x_ this is a regular Kalaman filter, in case h = h(x),
 * where h is non linear mapping and H_ is Jacobian, this would be an extended filter.
 * @param z - measurement vector
 * @param h - this values is used in the followin equation: y = z - h,
 *            so it could be y = z - H_ * x_ for the regular filter,
 *            or y = z - h(x_) for the extended filter.
 */
void KalmanFilter::Update(const VectorXd &z, const VectorXd &h)
{
    VectorXd y = z - h;
    MatrixXd H_t = H_.transpose();
    MatrixXd S = (H_ * state_.P_ * H_t) + R_;
    MatrixXd K = state_.P_ * H_t * S.inverse();

    state_.x_ = state_.x_ + (K * y);
    state_.P_ = (I_ - (K * H_)) * state_.P_;
}


