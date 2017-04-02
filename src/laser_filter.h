#ifndef EXTENDEDKF_LASER_FILTER_H
#define EXTENDEDKF_LASER_FILTER_H


#include "sensor_filter_base.h"

/**
 * Represents a particular filter for processing of laser measurments.
 */
class LaserFilter : public SensorFilterBase
{
    public:
        /**
         * Constructor. Initializes laser measurement noise and measurement matices and memorizes the state.
         * @param state
         */
        LaserFilter(KalmanFilterState &state);

        /**
         * Converts raw measuremnt vector to Vector(4) cartesian vector.
         * Laser measures only x, y so velocities are set to zero.
         *
         * @param raw_measurement - Vector(2) of x and y
         * @param x - Vector(4) of x, y, vx, vy
         */
        void GetCartesianStateVector(const Eigen::VectorXd &raw_measurement, Eigen::VectorXd &x) override;

};

#endif //EXTENDEDKF_LASER_FILTER_H
