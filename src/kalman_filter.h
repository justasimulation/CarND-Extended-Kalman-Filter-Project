#ifndef EXTENDEDKF_KALMAN_FILTER_H
#define EXTENDEDKF_KALMAN_FILTER_H

#include "Eigen/Dense"
#include "kalman_filter_state.h"

/**
 * Represents a general Kalman filter.
 * The filter consists of two parts: KalmanFilterState and KalmanFilter itself.
 * The separation was done in order to support update of the state by differen filters e.g. laser and rader.
 * This class as well as KalamanFilterState is quite general and does not contain any information about
 * initial values or sizes of matrices etc.
 */
class KalmanFilter
{
    protected:
        //x_ and P_ are moved outside so they can be updated by different instances of filters
        KalmanFilterState &state_;

        //state transition matrix
        Eigen::MatrixXd F_;

        //process covariance matrix
        Eigen::MatrixXd Q_;

        //measurement matrix
        Eigen::MatrixXd H_;

        //measurement covariance matrix
        Eigen::MatrixXd R_;

        //identity matrix
        Eigen::MatrixXd I_;

    public:
        /**
         * Copnstructor. Memorizes state.
         * @param state
         */
        KalmanFilter(KalmanFilterState &state);

        /**
         * Performs prediction step of the filter.
         */
        void Predict();

        /**
         * Performs update step of the filter.
         * @param z - measurement vector
         */
        void virtual Update(const Eigen::VectorXd &z);

    protected:
        /**
         * Performs update step of the filter.
         * Allows to implement extended Kalman filter.
         * In case h = H_ * x_ this is a regular Kalaman filter, in case h = h(x),
         * where h is mapping to polar and H_ is Jacobian, this would be an extended filter.
         * @param z - measurement vector
         * @param h - this values is used in the followin equation: y = z - h,
         *            so it could be y = z - H_ * x_ for the regular filter,
         *            or y = z - h(x_) for the extended filter.
         */
        void Update(const Eigen::VectorXd &z, const Eigen::VectorXd &h);
};


#endif //EXTENDEDKF_KALMAN_FILTER_H
