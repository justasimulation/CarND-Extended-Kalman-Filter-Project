#ifndef EXTENDEDKF_RADAR_FILTER_H
#define EXTENDEDKF_RADAR_FILTER_H

#include "Eigen/Dense"

#include "sensor_filter_base.h"

/**
 * Represetns a particular filter for processing radar measurements.
 */
class RadarFilter : public SensorFilterBase
{
    public:
        /**
         * Constructor. Initializes noise matrix, Jacobian and memorizes given state
         *
         * @param state
         */
        RadarFilter(KalmanFilterState &state);


        /**
         * Perorms update step of extended Kalamn filter.
         * First map current state to polar coordinates and then perform regular Kalman filter update using Jacobian as
         * H_ matrix.
         *
         * @param z - Vector(3) of ro, phi, ro_dot
         */
        void Update(const Eigen::VectorXd &z) override;

        /**
         * Converts raw measuremnt Vector(3) to cartesian Vector(4).
         * Radar measures only ro, phi and ro_dot so the need to be converted to x, y, vx, vy
         *
         * @param raw_measurement - Vector(3) of ro, phi, ro_dot
         * @param x - Vector(4) of x, y, vx, vy
         */
        void GetCartesianStateVector(const Eigen::VectorXd &measurement, Eigen::VectorXd &x) override;
};

#endif //EXTENDEDKF_RADAR_FILTER_H
