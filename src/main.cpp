#include <iostream>
#include "../include/DoublePendulum.h"
#include "../include/EulerIntegrator.h"

int main() {
    DoublePendulum pendulum;

    pendulum.parameters={2.0, 1.5, 1.0, 1.0, 9.8};
    pendulum.state = {1.0, 0.5, 2.0, 1.0};

    double dt = 0.001;



    for (int i = 0; i < 10000; i++) {
        Derivative d = pendulum.derivatives(pendulum.state);
        State newState = step(pendulum.state, d, dt);

        pendulum.state = newState;

        if (i % 100 == 0) {
            std::cout << "t = " << i * dt
                      << " | theta1 = " << pendulum.state.theta1
                      << " | theta2 = " << pendulum.state.theta2
                      << '\n';
        }
    }








}
