#include "../include/DoublePendulum.h"
#include "cmath"


Derivative DoublePendulum::derivatives(const State &s) const {

    double delta = s.theta1 - s.theta2;

    // Acceleration 1:
    double nr1 = -parameters.m2 * parameters.l2 * s.omega2 * s.omega2 * std::sin(delta);
    nr1 -= parameters.g * std::sin(s.theta1) * (parameters.m1 + parameters.m2);
    nr1 -= parameters.m2 * parameters.l1 * s.omega1 * s.omega1 * std::sin(delta) * std::cos(delta);
    nr1 += parameters.m2 * std::cos(delta) * parameters.g * std::sin(s.theta2);

    double dr1 = parameters.l1 * (parameters.m1 + parameters.m2) - (parameters.l1 * parameters.m2 * std::cos(delta) * std::cos(delta));

    double a1 = nr1 / dr1;

    // Acceleration 2:
    double nr2 = parameters.l1 * (parameters.m1 + parameters.m2) * s.omega1 * s.omega1 * std::sin(delta);
    nr2 -= (parameters.m1 + parameters.m2) * parameters.g * std::sin(s.theta2);
    nr2 += parameters.m2 * parameters.l2 * s.omega2 * s.omega2 * std::cos(delta) * std::sin(delta);
    nr2 += parameters.g * std::sin(s.theta1) * std::cos(delta) * (parameters.m1 + parameters.m2);

    double dr2 = parameters.l2 * (parameters.m1 + parameters.m2) - (parameters.m2 * parameters.l2 * std::cos(delta) * std::cos(delta));

    double a2 = nr2 / dr2;

    return {s.omega1,s.omega2,a1,a2};

}

double DoublePendulum::energy(const State &s) const {
    // nrg eqn
}
