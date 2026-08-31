#include "iostream"
#include "../include/DoublePendulum.h"

int main() {
    DoublePendulum pendulum;

    pendulum.parameters={2.0, 1.5, 1.0, 1.0, 9.8};
    // pendulum.state = {1.0, 0.5, 0,0};

    pendulum.state = {1.0, 0.5, 2.0, 1.0};

    Derivative d = pendulum.derivatives(pendulum.state);

    std::cout << "dtheta1/dt: " << d.theta1 << '\n';
    std::cout << "dtheta2/dt: " << d.theta2 << '\n';
    std::cout << "domega1/dt: " << d.omega1 << '\n';
    std::cout << "domega2/dt: " << d.omega2 << '\n';
}
