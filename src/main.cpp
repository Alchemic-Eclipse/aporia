#include <iostream>
#include "../include/DoublePendulum.h"
#include "../include/EulerIntegrator.h"
#include "../include/renderer.h"
#include "../include/RK4Integrator.h"
#include <raylib.h>


int main() {
    DoublePendulum pendulum;

    pendulum.parameters={2.0, 1.5, 50.0, 50.0, 9.8};
    pendulum.state = {1.0, 0.5, 2.0, 1.0};


    double dt = 0.01;

    // EulerIntegrator integrator;
    RK4Integrator integrator;

    initializeRenderer();

    double initialEnergy = pendulum.energy(pendulum.state); // E(0)

    while (!WindowShouldClose()) {

        // Physics
        pendulum.state = integrator.step(pendulum, pendulum.state, dt);

        double currentEnergy = pendulum.energy(pendulum.state); // E(t)

        // Rendering
        renderFrame(pendulum);
        std::cout
                 << " | Energy difference = " <<  (currentEnergy - initialEnergy)
                 << " | Energy Error (in %) = " << std::abs((currentEnergy - initialEnergy) / initialEnergy) * 100
                 << '\n';

    }

        closeRenderer();
    }

