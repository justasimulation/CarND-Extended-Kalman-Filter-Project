#include "Eigen/Dense"

#include "laser_filter.h"

using namespace Eigen;

/**
 * Constructor. Initializes laser measurement noise and measurement matices and memorizes the state.
 * @param state
 */
LaserFilter::LaserFilter(KalmanFilterState &state) : SensorFilterBase(state)
{
    R_ = MatrixXd(2, 2);
    R_ <<   0.0225, 0,
            0,      0.0225;

    H_ = MatrixXd(2, 4);
    H_ <<   1, 0, 0, 0,
            0, 1, 0, 0;
}

/**
 * Converts raw measuremnt vector to Vector(4) cartesian vector.
 * Laser measures only x, y so velocities are set to zero.
 *
 * @param raw_measurement - Vector(2) of x and y
 * @param x - Vector(4)
 */
void LaserFilter::GetCartesianStateVector(const VectorXd &raw_measurement, VectorXd &x)
{
    x << raw_measurement(0), raw_measurement(1), 0, 0;
}

