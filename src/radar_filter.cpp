#include "Eigen/Dense"

#include "radar_filter.h"

using namespace Eigen;

/**
 * Constructor. Initializes nose matrix and Jacobian and memorizes given state
 *
 * @param state
 */
RadarFilter::RadarFilter(KalmanFilterState &state) : SensorFilterBase(state)
{
    R_ = MatrixXd(3, 3);
    R_ << 0.09,     0,      0,
            0,      0.0009, 0,
            0,      0,      0.09;

    H_ = MatrixXd(3, 4);
    H_ <<   0, 0, 0, 0,
            0, 0, 0, 0,
            0, 0, 0, 0;
}

/**
 * Perorms update step of extended Kalamn filter.
 * First map current state to polar coordinates and then perform regular Kalman filter update using Jacobian as
 * H_ matrix.
 *
 * @param z - Vector(3) of ro, phi, ro_dot
 */
void RadarFilter::Update(const Eigen::VectorXd &z)
{
    float px = state_.x_(0);
    float py = state_.x_(1);
    float vx = state_.x_(2);
    float vy = state_.x_(3);

    // calculate expressions needed for Jacobian and linearization.
    float c1 = (px * px) + (py * py);
    float c2 = sqrt(c1);
    float c3 = sqrt(c1 * c1 * c1);
    float c4 = (vx * py) - (vy * px);

    // c1 is in the denominator of both jacobian and leniarization function, so cannot be 0.
    // in case it is zero, we don't do update step and use the result of the prediction step as
    // our best guess
    if(fabs(c1) > 0.00001)
    {
        //calcualte Jacobian
        H_ <<   px/c2,      py/c2,      0,      0,
                -py/c1,     px/c1,      0,      0,
                py*c4/c3,   -px*c4/c3,  px/c2,  py/c2;


        //linearize current state
        Eigen::VectorXd h = VectorXd(3);
        h << c2, atan2(py, px), ((px * vx) + (py * vy)) / c2;

        //do regular Kalman filter update
        SensorFilterBase::Update(z, h);
    }
}

/**
 * Converts raw measuremnt vector to Vector(3) cartesian Vector(4).
 * Radar measures only ro, phi and ro_dot so the need to be converted to x, y, vx, vy
 *
 * @param raw_measurement - Vector(3) of ro, phi, ro_dot
 * @param x - Vector(4) of x, y, vx, vy
 */
void RadarFilter::GetCartesianStateVector(const VectorXd &measurement, VectorXd &x)
{
    float ro = measurement(0);
    float phi = measurement(1);
    float ro_dot = measurement(2);

    float px = ro * cos(phi);
    float py = ro * sin(phi);
    float vx = ro_dot * cos(phi);
    float vy = ro_dot * sin(phi);

    x << px, py, vx, vy;
}

