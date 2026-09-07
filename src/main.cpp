#include <iostream>
#include "../include/DoublePendulum.h"
#include "../include/EulerIntegrator.h"
#include "../include/renderer.h"
#include "../include/RK4Integrator.h"
#include "../include/simulation.h"
#include "../include/analysis.h"
#include <raylib.h>

int main() {
    DoublePendulum pendulum;

    pendulum.parameters={2.0, 1.5, 50.0, 50.0, 9.8};
    pendulum.state = {3.14, 0.5, 2.0, 4.0};

    State initialState = pendulum.state;


    double dt = 0.015;
    int steps = 1000;

    // EulerIntegrator integrator;
    RK4Integrator integrator;

    // Visual Rendering
    initializeRenderer();

    bool paused = false;

    while(!WindowShouldClose()) {

        if (IsKeyPressed(KEY_SPACE)) {
            paused = !paused;
        }

        if (!paused) {
            pendulum.state = integrator.step(pendulum, pendulum.state, dt);
        }

        if (IsKeyPressed(KEY_N) && paused) {
            pendulum.state = integrator.step(pendulum, pendulum.state, dt);
        }

        if (IsKeyPressed(KEY_R)) {
            pendulum.state = initialState;
        }
        renderFrame(pendulum);
    }

    // Numerical experiment
    std::vector<double> energyHistory = simulate(pendulum, integrator, dt, steps);

    double maxError = maxEnergyError(energyHistory);
    std::cout << "Max energy error = " << maxError << " %\n";

    closeRenderer();
}