#include "../include/RK4Integrator.h"

State RK4Integrator::step(const DoublePendulum &pendulum, const State &state, double dt) {

    Derivative k1 = pendulum.derivatives(state);

    State state2;
    state2.theta1 = state.theta1 + k1.theta1 * (0.5 * dt);
    state2.theta2 = state.theta2 + k1.theta2 * (0.5 * dt);
    state2.omega1 = state.omega1 + k1.omega1 * (0.5 * dt);
    state2.omega2 = state.omega2 + k1.omega2 * (0.5 * dt);

    Derivative k2 = pendulum.derivatives(state2);

    State state3;
    state3.theta1 = state.theta1 + k2.theta1 * (0.5 * dt);
    state3.theta2 = state.theta2 + k2.theta2 * (0.5 * dt);
    state3.omega1 = state.omega1 + k2.omega1 * (0.5 * dt);
    state3.omega2 = state.omega2 + k2.omega2 * (0.5 * dt);

    Derivative k3 = pendulum.derivatives(state3);

    State state4;
    state4.theta1 = state.theta1 + k3.theta1 * dt;
    state4.theta2 = state.theta2 + k3.theta2 * dt;
    state4.omega1 = state.omega1 + k3.omega1 * dt;
    state4.omega2 = state.omega2 + k3.omega2 * dt;

    Derivative k4 = pendulum.derivatives(state4);

    State newState;
    newState.theta1 = state.theta1 + (dt / 6) * (k1.theta1 + 2 * k2.theta1 + 2 * k3.theta1 + k4.theta1);
    newState.theta2 = state.theta2 + (dt / 6) * (k1.theta2 + 2 * k2.theta2 + 2 * k3.theta2 + k4.theta2);
    newState.omega1 = state.omega1 + (dt / 6) * (k1.omega1 + 2 * k2.omega1 + 2 * k3.omega1 + k4.omega1);
    newState.omega2 = state.omega2 + (dt / 6) * (k1.omega2 + 2 * k2.omega2 + 2 * k3.omega2 + k4.omega2);

    return newState;
}
