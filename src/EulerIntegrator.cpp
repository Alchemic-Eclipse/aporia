#include "../include/EulerIntegrator.h"

State EulerIntegrator::step(const DoublePendulum &pendulum, const State &state, double dt) {
    State newState;

    Derivative derivative = pendulum.derivatives(state);

    newState.theta1 = state.theta1 + derivative.theta1 * dt;
    newState.theta2 = state.theta2 + derivative.theta2 * dt;

    newState.omega1 = state.omega1 + derivative.omega1 * dt;
    newState.omega2 = state.omega2 + derivative.omega2 * dt;

    return newState;
}


